
-- Keep a log of any SQL queries you execute as you solve the mystery.

-- INFO
-- July 28 2020
-- Chamberlin Street
-- 10:15 AM
-- Interview - 3 witness (Courthouse {keyword})


-- CRIME SCENE REPORTS
SELECT * FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = 2020 AND street = 'Chamberlin Street';

-- Courthouse

-- ATM 
SELECT * FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2020 AND transaction_type = 'withdraw' AND atm_location = 'Fifer Street';

-- BANK
SELECT * FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2020 AND transaction_type = 'withdraw' AND atm_location = 'Fifer Street');

-- INTERVIEWS
SELECT * FROM interviews WHERE day = 28 AND month = 7 AND year = 2020 AND transcript LIKE '%courthouse%';
-- thief get into car and leave parking lot within 10 minutes of theft ---- RUTH 
-- don't know name, reognized, thief withdrawing money from atm on fifer street  ---EUGENE 
-- thief called and talked for less tham 1 min, planning to take earliet flight out of fiftyville tomorrow, asked person to purchase ticket ---- RAYMOND 




-- QUERIES in ORDER
SELECT * FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = 2020 AND street = 'Chamberlin Street';
SELECT * FROM interviews WHERE day = 28 AND month = 7 AND year = 2020 AND transcript LIKE '%courthouse%';

SELECT * FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2020 AND transaction_type = 'withdraw' AND atm_location = 'Fifer Street';
SELECT * FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2020 AND transaction_type = 'withdraw' AND atm_location = 'Fifer Street');
SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2020 AND transaction_type = 'withdraw' AND atm_location = 'Fifer Street'));

SELECT * FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020 AND activity = 'exit' AND hour >= 10 AND minute >=15 AND minute <=25;
SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020 AND activity = 'exit' AND hour >= 10 AND minute >=15 AND minute <=25;

SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2020 AND duration <= 60;
SELECT * FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2020 AND duration <= 60);

SELECT * FROM airports WHERE city = 'Fiftyville'; --id:8
SELECT * FROM flights WHERE day = 29 AND month = 7 AND year = 2020 AND origin_airport_id = 8;
SELECT * FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE day = 29 AND month = 7 AND year = 2020 AND origin_airport_id = 8);
SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE day = 29 AND month = 7 AND year = 2020 AND origin_airport_id = 8));
SELECT * FROM people WHERE phone_number = '(375) 555-8161';
SELECT * FROM people WHERE phone_number = '(725) 555-3243';
sqlite> SELECT * FROM passengers  WHERE passport_number = 5773159633; -- Ernest FLight
SELECT * from flights WHERE id = 36; -- ERnest Flight
SELECT * FROM airports WHERE city = 'Fiftyville';
SELECT * FROM airports WHeRE id = 4; -- london airport
SELECT * FROM passengers  WHERE passport_number = 3592750733; -- RUSSELL FLIGHT



--SUSPECTS ATM
id | name | phone_number | passport_number | license_plate
395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
438727 | Victoria | (338) 555-6650 | 9586786673 | 8X428L0
449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
458378 | Roy | (122) 555-4581 | 4408372428 | QX4YZN3
467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

-- SUSPECTS COurthouse
id | name | phone_number | passport_number | license_plate
221103 | Patrick | (725) 555-4692 | 2963008352 | 5P2BI95
243696 | Amber | (301) 555-4174 | 7526138472 | 6P58WS2
325548 | Brandon | (771) 555-6667 | 7874488539 | R3G7486
396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
565511 | Vincent |  | 3011089587 | 94MV71O
682850 | Ethan | (594) 555-6254 | 2996517496 | NAW9653
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
745650 | Sophia | (027) 555-1068 | 3642612721 | 13FNH73
748674 | Jeremy | (194) 555-5027 | 1207566299 | V47T75I

--SUSPECTS CALL
id | name | phone_number | passport_number | license_plate
395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
438727 | Victoria | (338) 555-6650 | 9586786673 | 8X428L0
449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
561160 | Kathryn | (609) 555-5876 | 6121106406 | 4ZY7I8T
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
907148 | Kimberly | (031) 555-6622 | 9628244268 | Q12B3Z3

-- FINAL SUSPECT
Ernest
Russell


--soft suspect (3/4)
Bobby
Madison
Danielle

-- SUSPECTS flight
id | name | phone_number | passport_number | license_plate
205082 | Pamela | (113) 555-7544 | 1050247273 | 5CIO816
210245 | Jordan | (328) 555-9658 | 7951366683 | HW0488P
210641 | Heather | (502) 555-6712 | 4356447308 | 
251693 | Larry | (892) 555-8872 | 2312901747 | O268ZZ0
253397 | Diana | (918) 555-2946 | 6131360461 | P743G7C
325548 | Brandon | (771) 555-6667 | 7874488539 | R3G7486
341739 | Rebecca | (891) 555-5672 | 6264773605 | 
354903 | Marilyn | (568) 555-3190 | 7441135547 | 0R0FW39
395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
423393 | Carol | (168) 555-6126 | 6128131458 | 81MNC9R
447494 | Dennis |  | 4149859587 | 
449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
458378 | Roy | (122) 555-4581 | 4408372428 | QX4YZN3
467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
542503 | Michael | (529) 555-7276 | 6117294637 | HOD8639
560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
619074 | Matthew |  | 4195341387 | 31GVT84
626361 | Melissa | (717) 555-1342 | 7834357192 | 
651714 | Edward | (328) 555-1152 | 1540955065 | 130LD9Z
660982 | Thomas | (286) 555-0131 | 6034823042 | WD5M8I6
676919 | Steven | (195) 555-4173 | 1151340634 | 5VFD6G0
677698 | John | (016) 555-9166 | 8174538026 | 4468KVT
682850 | Ethan | (594) 555-6254 | 2996517496 | NAW9653
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X  ---- ERNEST
710572 | Richard |  | 7894166154 | 20Q418R
745650 | Sophia | (027) 555-1068 | 3642612721 | 13FNH73
750165 | Daniel | (971) 555-6468 | 7597790505 | FLFN3W0
753885 | Jennifer | (911) 555-0229 | 7378796210 | 1K44SN8
757606 | Douglas | (491) 555-2505 | 3231999695 | 1FW4EUJ
769190 | Charles | (427) 555-0556 | 3915621712 | R12SA4D
788213 | Emily | (406) 555-4440 | 6263461050 | Y340743
788911 | Gloria | (973) 555-3809 | 2835165196 | O010420
809265 | Jose | (914) 555-5994 | 9183348466 | 
952462 | Christian |  | 2626335085 | 6CV51G1
953679 | Doris | (066) 555-9701 | 7214083635 | M51FA04

-- russell and ernest both in flight suspect list 




-- PHONE CALLER RECIEVER
221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51
224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36
233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45  ---- ERNEST is CALLER  ---- RECIEVER is Berthold
234 | (609) 555-5876 | (389) 555-5198 | 2020 | 7 | 28 | 60
251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50
254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49 ---- Russell is caller   ---- RECIEVER is PHILIP
261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7 | 28 | 38
279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55
281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54


-- ERNEST FLIGHT
flight_id | passport_number | seat
36 | 5773159633 | 4A

id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20

-- LONDON AIRPORT is destination

-- RUSSELL FLIGHT
flight_id | passport_number | seat
18 | 3592750733 | 4C
24 | 3592750733 | 2C
54 | 3592750733 | 6C

id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0
24 | 7 | 8 | 2020 | 7 | 30 | 16 | 27
54 | 8 | 5 | 2020 | 7 | 30 | 10 | 19

-- RUSSELLS FLIGHTS ARE NOT ON THE DAY OF EVENT 
-- THEREFORE ERNEST MUST BE SUSPECT


--- Airports
id | abbreviation | full_name | city
8 | CSF | Fiftyville Regional Airport | Fiftyville

id | abbreviation | full_name | city
4 | LHR | Heathrow Airport | London
