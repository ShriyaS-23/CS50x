import os
import datetime
import math

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_transactions = db.execute('SELECT * FROM transactions WHERE user_id=:id', id=session['user_id'])
    share_dic = {}

    for transaction in user_transactions:
        if transaction['symbol'] in share_dic and transaction['type'] == 1:
            share_dic[transaction['symbol']] += transaction['shares']
        elif transaction['symbol'] in share_dic and transaction['type'] == 0:
           share_dic[transaction['symbol']] -= transaction['shares']
        else:
           share_dic[transaction['symbol']] = transaction['shares']

        if share_dic[transaction['symbol']] == 0:
            del share_dic[transaction['symbol']]

    holding = []
    for share in share_dic.keys():
        holding.append(lookup(share))

    conditions = zip(share_dic,range(len(share_dic)))
    cash = db.execute('SELECT cash FROM users WHERE id=:id', id=session['user_id'])

    return render_template('index.html', shares=share_dic, holding=holding, conditions=conditions, cash=round(cash[0]['cash'],2))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == 'GET':
        return render_template('buy.html')

    if request.method == 'POST':

        buy_symbol = request.form.get('symbol')
        buy_share = request.form.get('shares')

        if not buy_symbol:
            return apology('must provide symbol', 403)

        if not buy_share:
            return apology('must provide shares', 403)

        buy_request = lookup(buy_symbol)

        if buy_request == None:
            return apology('invalid symbol', 400)
            
        try:
            x = int(buy_share)
        except ValueError:
            return apology("must be a positive integer", 400)

        user_cash = db.execute('SELECT cash FROM users WHERE id=:id', id=session['user_id'])

        unit_price = float(buy_request['price'])
        total_price = unit_price*float(buy_share)

        if total_price > user_cash[0]['cash']:
            return apology('insufficient balance', 403)

        time = datetime.datetime.now()
        year = str(time.year)
        month = str(time.month)
        day = str(time.day)

        date = day + '/' + month + '/' + year

        db.execute('INSERT INTO transactions (user_id, shares, symbol, name, unit_price, total_price, date, type) VALUES (?,?,?,?,?,?,?,?)', session['user_id'], buy_share, buy_symbol, buy_request['name'], unit_price, total_price, date, 1)

        final_cash = float(user_cash[0]['cash']) - total_price

        db.execute('UPDATE users SET cash=:final_cash WHERE id=:user_id', final_cash=final_cash, user_id=session['user_id'])

        return render_template('bought.html', price=total_price, symbol=buy_symbol)
        


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_transactions = db.execute('SELECT * FROM transactions WHERE user_id=:user_id', user_id=session['user_id'])
    return render_template('history.html', transactions = user_transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == 'GET':
        return render_template('quote.html')

    if request.method == 'POST':
        quote_request = lookup(request.form.get('symbol'))
        if quote_request == None:
            return apology('invalid symbol', 400)
        return render_template('quoted.html', quote=quote_request)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method ==  'GET':
        return render_template('register.html')

    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        if not username:
            return apology('must provide username', 400)

        if not password:
            return apology('must provide password', 400)

        if not request.form.get('confirmation'):
            return apology('must confirm password', 400)

        if password != request.form.get('confirmation'):
            return apology('password does not match confirmation' , 400)

        userCheck = db.execute('SELECT COUNT(username) FROM users WHERE username = :username', username=username)
        if userCheck[0]['COUNT(username)'] != 0:
            return apology ('username already exists', 400)

        hash_val = generate_password_hash(password)
        db.execute('INSERT INTO users (username,hash) VALUES (?,?)', username, hash_val)

        return redirect('/')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == 'GET':
        user_transactions = db.execute('SELECT * FROM transactions WHERE user_id=:id', id=session['user_id'])
        share_dic = {}

        for transaction in user_transactions:
            if transaction['symbol'] in share_dic and transaction['type'] == 1:
                share_dic[transaction['symbol']] += transaction['shares']
            elif transaction['symbol'] in share_dic and transaction['type'] == 0:
               share_dic[transaction['symbol']] -= transaction['shares']
            else:
               share_dic[transaction['symbol']] = transaction['shares']

        return render_template('sell.html', shares=share_dic)

    if request.method == 'POST':

        sell_symbol = request.form.get('sell_symbol')
        sell_share = request.form.get('share')

        if not sell_symbol:
            return apology('must provide symbol', 403)

        if not sell_share:
            return apology('must provide shares', 403)

        sell_request = lookup(sell_symbol)

        user_cash = db.execute('SELECT cash FROM users WHERE id=:id', id=session['user_id'])

        unit_price = float(sell_request['price'])
        total_price = unit_price*float(sell_share)

        time = datetime.datetime.now()
        year = str(time.year)
        month = str(time.month)
        day = str(time.day)

        date = day + '/' + month + '/' + year

        db.execute('INSERT INTO transactions (user_id, shares, symbol, name, unit_price, total_price, date, type) VALUES (?,?,?,?,?,?,?,?)', session['user_id'], sell_share, sell_symbol, sell_request['name'], unit_price, total_price, date, 0)

        final_cash = float(user_cash[0]['cash']) + total_price

        db.execute('UPDATE users SET cash=:final_cash WHERE id=:user_id', final_cash=final_cash, user_id=session['user_id'])

        return redirect('/')

@app.route('/add-money', methods=['GET', 'POST'])
@login_required
def add_money():

    if request.method == 'GET':
        username = db.execute('SELECT username FROM users WHERE id=:id', id=session['user_id'])
        return render_template('add-money.html', username=username[0]['username'])

    if request.method == 'POST':
        money_pass = request.form.get('money_pass')
        amount = request.form.get('money')

        if not money_pass:
            return apology('must enter password', 403)

        if not amount:
            return apology('must enter amount', 403)

        user_pass = db.execute('SELECT hash FROM users WHERE id=:id', id=session['user_id'])

        if not check_password_hash(user_pass[0]['hash'], money_pass):
            return apology('incorrect password', 400)

        cash = db.execute('SELECT cash FROM users WHERE id=:id', id=session['user_id'])
        add_cash = cash[0]['cash'] + float(amount)

        db.execute('UPDATE users SET cash=:cash WHERE id=:id', cash=add_cash, id=session['user_id'])

        return redirect('/')


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

