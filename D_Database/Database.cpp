#include "Database.h"


Database::Connection::Connection()
    : m_Server("localhost"),
      m_User("root"),
      m_Pass("test112"),
      m_DB("db"),
      m_Connect(mysql_init(m_Connect)) {}


Database::Connection::Connection(const char* Server, const char* User, const char* Pass,
                     const char* DB)
    : m_Server(Server),
      m_User(User),
      m_Pass(Pass),
      m_DB(DB),
      m_Connect(mysql_init(m_Connect)) {}

Database::Connection::~Connection() {}


void Database::Connection::Check_Error() {
  if (mysql_errno(m_Connect) != NULL) {
    std::cout << "Fehler: " << mysql_errno(m_Connect) << mysql_error(m_Connect)
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Database::Connection::Connect() {
  Check_Error();     /* mit dem Server verbinden */
  mysql_real_connect(m_Connect, m_Server, m_User, m_Pass, m_DB, 0, 0, 0);
  Check_Error();
 }
void Database::Connection::Disconnect() {
   if (m_Connect > 0) {
     mysql_close(m_Connect);
   } 
}
  
void Database::Connection::Query() {
  unsigned long length = 0;
  Connect();
  const char* m_Query;
  MYSQL_RES* result;
  MYSQL_ROW row;
  int state;
  state = mysql_query(m_Connect, "SELECT * FROM kunde");
  if (state != 0) {
    printf(mysql_error(m_Connect));
    exit(EXIT_SUCCESS);
  }
  /* must call mysql_store_result() before we can issue any * other query
       calls */
  result = mysql_store_result(m_Connect);
  std::cout << "Rows: " << mysql_num_rows(result)
            << std::endl; /* process each row in the result set */
  while ((row = mysql_fetch_row(result)) != NULL) {
    std::cout << "id: " << (row[0] ? row[0] : "NULL") << " "
              << "val : " << (row[1] ? row[1] : "NULL") << std::endl;
    
  }                          /* free the result set */
  mysql_free_result(result); /* close the connection */
  mysql_close(m_Connect);
  printf("Done.\n");
}
// end of class Conn

Database::Statement::Statement()
    : Connection(),
      m_Query("select * from kunde") { }

Database::Statement::Statement(const char* Query) : m_Query(Query) {}
Database::Statement::~Statement() { }

void Database::Statement::get_Data() {


 /* must call mysql_store_result() before we can issue any * other query
       calls */
  unsigned long length = 0;
 state = mysql_query(m_Connect, "SELECT * FROM kunde");
  if (state != 0) {
   printf(mysql_error(m_Connect));
    exit(EXIT_SUCCESS);
  }
  /* must call mysql_store_result() before we can issue any * other query
       calls */
  result = mysql_store_result(m_Connect);
  std::cout << "Rows: "<< mysql_num_rows(result) << std::endl; /* process each row in the result set */
  while ((row = mysql_fetch_row(result)) != NULL) {
    std::cout << "id: " << (row[0] ? row[0] : "NULL") << "val : " <<(row[1] ? row[1] : "NULL") << std::endl;
  }                          /* free the result set */
  mysql_free_result(result); /* close the connection */
  mysql_close(m_Connect);
  printf("Done.\n");

  /*unsigned long length=0;
  if (!mysql_real_query(Connect(), m_Query, length)) {
    m_Res_set = mysql_store_result(Connect());
    while (m_Rrow = mysql_fetch_row(m_Res_set)) {
      printf("ID: %s, name: %s\n", m_Rrow[0], m_Rrow[1]); }
  } else {
    puts("Die Anfrage konnte nicht ausgefuehrt werden.");
  }*/ }