-- Keep a log of any SQL queries you execute as you solve the mystery.


-- **********querying crime scene reports table for July 28 2021
-- select * from crime_scene_reports
--     where year = 2021 and month = 7 and day =28 and street = 'Humphrey Street'
--     limit 5;

-- ********* querying interviews for July 28, 2021 & filtering by keyword "thief" results in 3 matching interview results
-- select name,transcript from interviews
--     where year = 2021 and month =7 and day = 28 and transcript like '%thief%';

-- ********* querying people's table for matches in bakery_security_logs and phone_calls
-- Bruce is the culprit
-- select name from people where
--     phone_number in (
--         select caller from phone_calls
--         where year =2021 and month = 7 and day = 28 and duration <=60
--         )
--     and license_plate in (
--         select license_plate from bakery_security_logs
--         where year = 2021 and month =7 and day = 28 and hour = 10 and
--         minute >= 15 and minute <=25 and activity = 'exit'
--         )
--     and id in (
--         select person_id from bank_accounts where account_number in (
--             select account_number from atm_transactions
--             where year =2021 and month = 7 and day = 28 and
--             atm_location = 'Leggett Street' and transaction_type = 'withdraw'
--             )
--         )
--     and passport_number in (
--         select passport_number from passengers where flight_id in (
--             select id from flights where year = 2021 and month = 7 and day = 29 and
--             origin_airport_id = (select id from airports where city = 'Fiftyville')
--             order by hour, minute limit 1
--             )
--         );

-- The accomplice is Robin
        -- select * from people where phone_number = (
        --     select receiver from phone_calls
        --     where year =2021 and month = 7 and day = 28 and duration <=60 and
        --     caller = (select phone_number from people where name = 'Bruce')
        -- );


-- And Bruce flew to New York city
select city from airports where id = (
            select destination_airport_id from flights where year = 2021 and month = 7 and day = 29 and
            origin_airport_id = (select id from airports where city = 'Fiftyville')
            order by hour, minute limit 1
);



--  Rough work below
--

--  Notes from investigation
-- rubber duck got stolen at around 10:15 am
-- things to investigate from interviews:
-- thief got into car in bakery parking lot (within 10 minutes of 10:!5)

-- excerpts from investigation
-- ******************************************
-- *********************from crime_scene_reports
-- *******************************************
    --  295 | 2021 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |

-- ********************************************
-- ************************from interviews
-- *********************************************
-- | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |