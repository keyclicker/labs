import mysql.connector


class Database:
    def __init__(self):
        self.db = mysql.connector.connect(
            host="localhost",
            user="root",
            password="password",
            database="airport"
        )

        self.cursor = self.db.cursor(buffered=True)
        self.cursor.execute("SHOW DATABASES")

    def fetch(self, query):
        try:
            self.cursor.execute(query)
            return self.cursor.fetchall()
        except Exception as e:
            print(e)
            return None

    def commit(self, query):
        try:
            self.cursor.execute(query)
            self.db.commit()
        except Exception as e:
            print(e)
            self.db.rollback()

    def get_airlines(self):
        return self.fetch("select * from airlines")

    def get_flights(self):
        return self.fetch("select * from flights")

    def get_airline_flights(self, id_a):
        return self.fetch("select * from flights where id_a = %d" % id_a)

    def get_airline(self, id_a):
        res = self.fetch("select * from airlines where id_a = %d" % id_a)
        return res[0] if len(res) == 1 else None

    def get_flight(self, id_f):
        res = self.fetch("select * from flights where id_f = %d" % id_f)
        return res[0] if len(res) == 1 else None

    def add_airline(self, id_a, name, city):
        self.commit("insert into airlines "
                    "values (%d, '%s', '%s')" % (id_a, name, city))

    def add_flight(self, id_f, id_a, _from, to):
        self.commit("insert into flights "
                    "values (%s, '%s', '%s', '%s')" %
                    (str(id_f), id_a, _from, to))

    def update_airline(self, id_a, name, city):
        self.commit("update airlines "
                    "set name = '%s', city = '%s' "
                    "where  id_a = %d" % (name, city, id_a))

    def update_flight(self, id_f, _from, to):
        self.commit("update flights "
                    "set `from` = '%s', `to` = '%s' "
                    "where id_f = %d" % (_from, to, id_f))

    def remove_airline(self, id_a):
        self.commit("delete from airlines "
                    "where id_a = %d" % id_a)

    def remove_flight(self, id_f):
        self.commit("delete from flights "
                    "where id_f = %d" % id_f)