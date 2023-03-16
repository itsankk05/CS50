-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT id, description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Humphrey Street";
SELECT id, caller, receiver, duration FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2021;

SELECT id, name, transcript FROM interviews WHERE month = 7 AND day = 28 AND year = 2021;
SELECT id FROM airports WHERE city = "Fiftyville";
SELECT id, destination_airport_id, hour, minute FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND day = 29 AND month = 7 AND year = 2021;
SELECT * FROM airports WHERE id = 4;
SELECT * FROM passengers WHERE flight_id = 36;
SELECT id, name FROM interviews WHERE name IN (SELECT id, name, phone_number FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36));
SELECT id, caller, receiver, duration FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2021 AND duration < 60;
SELECT id, account_number, amount FROM atm_transactions WHERE month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%Leggett Street%";
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%Leggett Street%");


SELECT id, name, phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%Leggett Street%"));
--Kenny, Iman, Benista, Taylor, Brooke, Luca, Diana, Bruce
INTERSECT
SELECT id, name, phone_number FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);
-- Kenny, Sofia, Taylor, Luca, Kelsey, Edward, Bruce, Doris
INTERSECT
SELECT id, name, phone_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2021 AND duration < 60);
--Kenny, Sofia, Benista, Taylor, Diana, Kelsey, Bruce, Carina

--Main Suspects- Kenny, Taylor, Bruce

SELECT id, license_plate, hour, minute,activity FROM bakery_security_logs WHERE month = 7 AND day = 28 AND activity = "exit" AND hour = 10 AND minute > 15 AND minute < 25;
SELECT id, name FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND activity = "exit" AND hour = 10 AND minute > 15 AND minute < 25);
--Vanessa, Barry, Iman, Sofia, Luca, Diana, Kelsey, Bruce

--Theif is BRUCE

SELECT id, phone_number FROM people WHERE name = "Bruce";
SELECT receiver FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE name = "Bruce") AND month = 7 AND day = 28 AND year = 2021 AND duration < 60;
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE name = "Bruce") AND month = 7 AND day = 28 AND year = 2021 AND duration < 60);

--Accomplice is ROBIN
