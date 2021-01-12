import mysql.connector

## Creating a database called 'phoenix'
db = mysql.connector.connect(
    host = 'localhost',
    user = 'root',
    passwd = 'anat',
    database = 'phoenix'
)

cursor = db.cursor()

## The 'EXECUTE' command is being used to compile a SQL statement
# cursor.execute("CREATE DATABASE phoenix")
# cursor.execute("SHOW DATABASES")
# databases = cursor.fetchall()
#
# for database in databases:
#     print(database)

## Creating tables in the new database
# cursor.execute("CREATE TABLE
#                   polisot_test(mis_polisa INT, mis_hevra INT, mis_mevutach INT, tar_hathala_pol DATE)")
# cursor.execute("CREATE TABLE
#                   mevutahim_test(kod_bit VARCHAR(1), mis_mevutach INT)")
# cursor.execute("CREATE TABLE
#                   payments_test(tar_tashlum DATE, schum_tashlum INT, mis_polisa int)")
# cursor.execute("CREATE TABLE
#                   dim_kod_bituach_test(kod_bit VARCHAR(1), teur_kod_bit VARCHAR(6))")
#

# cursor.execute("SHOW TABLES")
# tables = cursor.fetchall()
#
# for table in tables:
#     print(table)

# cursor.execute("ALTER TABLE polisot_test ADD PRIMARY KEY(mis_polisa)")
# cursor.execute("ALTER TABLE payments_test ADD PRIMARY KEY(mis_polisa)")


# Inserting single data into polisot_test:
# query = "INSERT INTO
#               polisot_test (mis_polisa, mis_hevra, mis_mevutach, tar_hathala_pol)
#               VALUES (%s, %s, %s, %s)"
# values = (183, 1, 12345, '2014-01-23')
# cursor.execute(query, values)
#
# db.commit()
#
#
# Inserting multiple data into polisot_test:
# query = "INSERT INTO
#               polisot_test (mis_polisa, mis_hevra, mis_mevutach, tar_hathala_pol)
#               VALUES (%s, %s, %s, %s)"
# values = [
#     (225, 3, 12347, '2012-08-01'),
#     (303, 7, 3456789, '2014-07-18'),
#     (404, 3, 23147, '2013-09-08'),
#     (557, 7, 6586745, '2013-05-01'),
#     (707, 1, 1567, '2014-01-25'),
#     (524, 7, 12345, '2014-01-01'),
#     (425, 3, 12347, '2011-07-03'),
#     (410, 7, 2841, '2012-09-05'),
#     (754, 8, 1319, '2014-09-08')
# ]
#
# for value in values:
#     cursor.execute(query, value)
#
# db.commit()

# cursor.execute("SELECT * FROM polisot_test")
# records = cursor.fetchall()
#
# for record in records:
#     print(record)


# # Inserting multiple data into mevutahim_test(kod_bit VARCHAR(1), mis_mevutach INT):
# query = "INSERT INTO mevutahim_test (kod_bit, mis_mevutach) VALUES (%s, %s)"
# values = [
#     ('H', 12345),
#     ('P', 12347),
#     ('B', 3456789),
#     ('B', 23147),
#     ('H', 6586745),
#     ('H', 1567),
#     ('P', 12345),
#     ('H', 2841),
#     ('H', 12347),
#     ('G', 1319)
# ]
#
# for value in values:
#     cursor.execute(query, value)
#
# db.commit()
#
# cursor.execute("SELECT * FROM mevutahim_test")
# records = cursor.fetchall()
#
# for record in records:
#     print(record)

# Inserting multiple data into payments_test(tar_tashlum DATE, schum_tashlum INT, mis_polisa int):
# query = "INSERT INTO payments_test (tar_tashlum, schum_tashlum, mis_polisa) VALUES (%s, %s, %s)"
# values = [
#     ('2014-01-01', 500, 183),
#     ('2014-05-01', 70, 225),
#     ('2014-07-01', 125, 303),
#     ('2008-09-01', 458, 404),
#     ('2014-01-01', 105, 557),
#     ('2014-11-01', 780, 707),
#     ('2014-01-01', 417, 524),
#     ('2013-02-01', 432, 425),
#     ('2014-05-01', 751, 410),
#     ('2014-07-01', 785, 754),
# ]
#
# for value in values:
#     cursor.execute(query, value)
#
# db.commit()
#
# cursor.execute("SELECT * FROM payments_test")
# records = cursor.fetchall()
#
# for record in records:
#     print(record)

# Inserting multiple data into dim_kod_bituach_test(kod_bit VARCHAR(1), teur_kod_bit VARCHAR(6)):
# query = "INSERT INTO dim_kod_bituach_test (kod_bit, teur_kod_bit) VALUES (%s, %s)"
# values = [
#     ('H', 'haim'),
#     ('B', 'briut'),
#     ('P', 'pensia'),
#     ('R', 'rechev'),
# ]
#
# for value in values:
#     cursor.execute(query, value)
#
# db.commit()
#
# cursor.execute("SELECT * FROM dim_kod_bituach_test")
# records = cursor.fetchall()
#
# for record in records:
#     print(record)


# SELECT polisot_test.mis_polisa, polisot_test.mis_hevra, polisot_test.tar_hathala_pol FROM polisot_test WHERE EXISTS(SELECT )


#------------------------------------------------------------------------------#
#------------------------------------------------------------------------------#
#------------------------------------------------------------------------------#


# #1. מצא את כמות הפוליסות שיש לכל חברה.
# בתוצאה הצג בסדר עולה לפי מספר החברה את: מספר החברה וכמות הפוליסות השייכות לה.
# cursor.execute("SELECT
#                   mis_hevra, COUNT(mis_hevra)
#                   FROM polisot_test
#                   GROUP BY mis_hevra
#                   HAVING COUNT(mis_hevra) > 1")
# records = cursor.fetchall()
#
# for record in records:
#     print(record)


#------------------------------------------------------------------------------#


# 2. מצא את כמות החברות עם תאריך התחלת פוליסה החל משנת 2012.
# בתוצאה הצג את: כמות החברות
# cursor.execute("SELECT COUNT(*) FROM polisot_test WHERE YEAR(tar_hathala_pol) >= 2012")
# records = cursor.fetchall()
#
# for record in records:
#     print(record)


#------------------------------------------------------------------------------#


# 3. מצא את החברות שלהן יש יותר מ-2 פוליסות.
# בתוצאה הצג את: מספר החברה.
# cursor.execute("SELECT mis_hevra, COUNT(mis_hevra) FROM polisot_test GROUP BY mis_hevra HAVING COUNT(mis_hevra) > 2")
# records = cursor.fetchall()
#
# for record in records:
#     print(record)


#------------------------------------------------------------------------------#


#  4. מצא את התאריך המינימאלי של תאריך התחלת פוליסה לכל חברה.
# בתוצאה הצג את: מספר החברה ותאריך התחת הפוליסה המינימאלי.
# cursor.execute("SELECT mis_hevra, MIN(tar_hathala_pol) FROM polisot_test GROUP BY mis_hevra")
# records = cursor.fetchall()
#
# for record in records:
#     print(record)


#------------------------------------------------------------------------------#


# 5. מצא את סה"F סכום התשלום.
# בתוצאה הצג בסדר יורד לפי מספר הפוליסה את: מספר הפוליסה, מספר החברה וסה"כ סכום התשלום.
# # I added a foreign key between mispolisa in 'polisot_test' and 'payments_test':
# # cursor.execute("ALTER TABLE payments_test ADD FOREIGN KEY (mis_polisa) REFERENCES polisot_test(mis_polisa)")
# cursor.execute("""SELECT payments_test.mis_polisa, polisot_test.mis_hevra, payments_test.schum_tashlum
#                   FROM polisot_test
#                   LEFT JOIN payments_test ON polisot_test.mis_polisa=payments_test.mis_polisa
#                   ORDER BY payments_test.schum_tashlum DESC""")
# records = cursor.fetchall()
#
# for record in records:
#     print(record)


#------------------------------------------------------------------------------#


# 6. מצא את כל המבטחים והפוליסות שבוצע להם תשלום בשנת 2014.
# בתוצאה הצג את: המבוטח, מספר הפוליסה ותיאור קוד הביטוח.
# Many different ways to write the same thing:
# cursor.execute("""SELECT
#                     pol.mis_mevutach,
#                     pol.mis_polisa,
#                     kod.teur_kod_bit
#                   FROM polisot_test pol
#                   JOIN mevutahim_test mev
#                     ON pol.mis_mevutach=mev.mis_mevutach
#                   JOIN dim_kod_bituach_test kod
#                     ON mev.kod_bit=kod.kod_bit
#                   JOIN payments_test pay
#                     ON pol.mis_polisa=pay.mis_polisa
#                   WHERE YEAR(pay.tar_tashlum) = 2014
#                   """)
# cursor.execute("""SELECT
#                     pol.mis_mevutach,
#                     pol.mis_polisa
#                   FROM polisot_test pol
#                   JOIN payments_test pay
#                     ON pol.mis_polisa=pay.mis_polisa
#                     WHERE pay.mis_polisa
#                         IN (SELECT pay.mis_polisa
#                                 FROM payments_test pay
#                                 WHERE YEAR(pay.tar_tashlum) = 2014)
#                   """)
# cursor.execute("""SELECT DISTINCT
#                     pol.mis_mevutach,
#                     pol.mis_polisa,
#                     kod.teur_kod_bit
#                   FROM polisot_test pol, mevutahim_test mev, dim_kod_bituach_test kod, payments_test pay
#                   WHERE pol.mis_mevutach=mev.mis_mevutach AND pol.mis_polisa=pay.mis_polisa AND YEAR(pay.tar_tashlum) = 2014  AND mev.kod_bit=kod.kod_bit
#                   """)

# cursor.execute("""SELECT DISTINCT * FROM
#                 (
#                     SELECT DISTINCT
#                     pol.mis_mevutach,
#                     pol.mis_polisa,
#                     kod.teur_kod_bit
#                     FROM polisot_test pol, mevutahim_test mev, dim_kod_bituach_test kod, payments_test pay
#                     WHERE
#                         YEAR(pay.tar_tashlum) = 2014 AND
#                         pay.mis_polisa=pol.mis_polisa AND
#                         pol.mis_mevutach=mev.mis_mevutach AND
#                         mev.kod_bit=kod.kod_bit) AS t1
#                     UNION
#                     SELECT DISTINCT * FROM
#                     (SELECT DISTINCT
#                     pol.mis_mevutach,
#                     pol.mis_polisa,
#                     kod.teur_kod_bit
#                     FROM polisot_test pol, mevutahim_test mev, dim_kod_bituach_test kod, payments_test pay
#                     WHERE
#                         pol.mis_mevutach=mev.mis_mevutach) AS t2
#                   """)





# cursor.execute("""(SELECT
#                     pay.mis_polisa
#                     FROM payments_test pat
#                     WHERE YEAR(tar_tashlum) = 2014) as t1
#                   UNION
#                   SELECT DISTINCT * FROM
#                   (SELECT
#                     pol.mis_mevutach
#                     FROM polisot_test pol
#                     JOIN ) as t2
# """)


# cursor.execute("""SELECT
#                     pay.mis_polisa
#                     FROM payments_test pay
#                     WHERE YEAR(tar_tashlum) = 2014
#                     LEFT JOIN
#                     (
#                         SELECT
#                             pol.mis_mevutach,
#                             pol.mis_polisa,
#                         FROM
#                             polisot_test pol,
#                             mevutahim_test mev,
#                             dim_kod_bituach_test kod,
#                             payments_test pay
#                     )t1
#                     WHERE pol.mis_mevutach=mev.mis_mevutach AND pol.mis_polisa=pay.mis_polisa AND mev.kod_bit=kod.kod_bit
# """)




# cursor.execute("""SELECT * FROM(SELECT
#                     pay.mis_polisa
#                     FROM payments_test pay
#                     WHERE YEAR(tar_tashlum) = 2014) t1
#                   JOIN
#                   SELECT * FROM(SELECT
#                     pol.mis_mevutach
#                     FROM polisot_test pol, payments_test pay
#                     WHERE pol.mis_polisa=pay.mis_polisa) t2
#
#
#
# """)
# cursor.execute("""SELECT DISTINCT
#                     pol.mis_mevutach,
#                     pay.mis_polisa,
#                     kod.teur_kod_bit
#                     FROM payments_test pay
#                   JOIN
#                     polisot_test pol
#                     ON pol.mis_polisa=pay.mis_polisa
#                   JOIN
#                     mevutahim_test mev
#                     ON pol.mis_mevutach=mev.mis_mevutach
#
#                   JOIN
#                     dim_kod_bituach_test kod
#                     ON mev.kod_bit=kod.kod_bit
#                     WHERE YEAR(pay.tar_tashlum) = 2014
# """)
# cursor.execute("""SELECT DISTINCT
#                     pol.mis_mevutach,
#                     pol.mis_polisa,
#                     kod.teur_kod_bit
#                   FROM polisot_test pol, mevutahim_test mev, dim_kod_bituach_test kod
#                   JOIN
#                     payments_test pay
#                     ON pol.mis_mevutach=mev.mis_mevutach AND pol.mis_polisa=pay.mis_polisa AND mev.kod_bit=kod.kod_bit YEAR(pay.tar_tashlum) = 2014
#                   """)


# cursor.execute("""SELECT DISTINCT * FROM
#                     (SELECT DISTINCT
#                     pol.mis_mevutach,
#                     pol.mis_polisa,
#                     kod.teur_kod_bit
#                     FROM polisot_test pol, mevutahim_test mev, dim_kod_bituach_test kod, payments_test pay
#                     WHERE
#                         pol.mis_mevutach=mev.mis_mevutach AND pol.mis_polisa=pay.mis_polisa AND mev.kod_bit=kod.kod_bit AND YEAR(pay.tar_tashlum) = 2014) AS t2
# """)
#
# records = cursor.fetchall()
# ##                  WHERE YEAR(pay.tar_tashlum) IN (SELECT pay.mis_polisa FROM payments_test pay WHERE YEAR(pay.tar_tashlum) = 2014
# for record in records:
#     print(record)


# 7. מצא את כל המבוטחים, מספרי הפוליסות והתשלום עבור מבוטחים שקים להם רק קוד ביטוח אחד וסכום התשלום הוא פחות מ-700 שקל.
# בתוצאה הצג את: מספר המבוטח, מספר פוליסה והתשלום.
# A - BRUT FORCE:
# cursor.execute("""SELECT
#                         mev.mis_mevutach,
#                         pol.mis_mevutach,
#                         pay.schum_tashlum
#                     FROM
#                     polisot_test pol
#                     JOIN mevutahim_test mev ON pol.mis_mevutach=mev.mis_mevutach
#                     JOIN payments_test pay ON pay.mis_polisa=pol.mis_polisa
#                     WHERE pay.schum_tashlum < 700
#                     GROUP BY mev.mis_mevutach, pol.mis_mevutach, pay.schum_tashlum
#                     HAVING COUNT(mev.mis_mevutach) = 1
# """)

# B - USING VIEWS:
# B - step 1:
# cursor.execute("""CREATE OR REPLACE
#                     ALGORITHM = UNDEFINED VIEW `one_polisa` AS
#                     select
#                         *
#                     from
#                         `mevutahim_test` `mev`
#                     group by
#                         `mev`.`mis_mevutach`, `mev`.`kod_bit`
#                     having
#                         (count(`mev`.`mis_mevutach`) = 1)
# """)

# B - step 2:
# cursor.execute("""CREATE OR REPLACE
#                     ALGORITHM = UNDEFINED VIEW `under_700` AS
#                     select
#                         *
#                     from
#                         `payments_test` `pay`
#                     where
#                         (`pay`.`schum_tashlum` < 700)
# """)

# B - step 3a:
# cursor.execute("""CREATE VIEW single_mevutach AS
#                     select
#                         pol.mis_mevutach
#                     from
#                         polisot_test pol
#                     group by
#                         pol.mis_mevutach
#                     having
#                         count(mis_mevutach) = 1
# """)

# B - step 3b:
# cursor.execute(""" CREATE VIEW single_mev AS
#                     select
#                         pol.mis_polisa, pol.mis_mevutach
#                     from
#                         polisot_test pol
#                     join
#                         single_mevutach
#                         on pol.mis_mevutach=single_mevutach.mis_mevutach
# """)

# B - step 4:
# cursor.execute("""SELECT one.mis_mevutach, one.mis_polisa, un.schum_tashlum
#                     FROM under_700 un
#                      JOIN
#                      single_mev one
#                      ON one.mis_polisa=un.mis_polisa
# """)

records = cursor.fetchall()

for record in records:
    print(record)
