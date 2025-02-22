#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <sqlite3.h>
#include <SPIFFS.h>

const char *SSID = "ZFlip5 de Hugo";
const char *PASSWORD = "aquihaywifi";

sqlite3 *db;
const char *dbPath = "/data/people.db";

void insertarReto(int usuario_id, int reto_id, const char* estado);
void instertar_persona(const char *full_name, const char *email, const char *department, int rank);
void insertar_skill(const char *skill);
void get_user_skills(const char *full_name);
void get_users_by_skill(const char *skill_name);


void setup(){
    Serial.begin(115200);

    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    if (!SPIFFS.begin(true)){
        return;
    }

    // Crear base de datos SQLite
    if (sqlite3_open(dbPath, &db) == SQLITE_OK) {
        Serial.println("Base de datos abierta correctamente");
        const char* sql = 
        "CREATE TABLE IF NOT EXISTS usuarios ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "full_name TEXT NOT NULL, "
        "department TEXT, "
        "rank INTEGER, "
        "skill_id INTEGER, "
        "email TEXT UNIQUE, "
        "FOREIGN KEY (skill_id) REFERENCES skills(id));"
        

        "CREATE TABLE IF NOT EXISTS retos ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "user_id INTEGER, "
        "challenge_id INTEGER, "
        "state TEXT, "
        "FOREIGN KEY (user_id) REFERENCES usuarios(id));"

        "CREATE TABLE IF NOT EXISTS skills ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "skill_name TEXT NOT NULL, "
        "experience INTEGER CHECK (experience >= 0));"
        
        "CREATE TABLE usuario_skills ("
        "user_id INTEGER, "
        "skill_id INTEGER, "
        "FOREIGN KEY (user_id) REFERENCES usuarios(id), "
        "FOREIGN KEY (skill_id) REFERENCES skills(id), "
        "PRIMARY KEY (user_id, skill_id));";

        char* errMsg;
        if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
            Serial.print("Error al crear la tabla: ");
            Serial.println(errMsg);
            sqlite3_free(errMsg);
        }
    } else {
        Serial.println("Error al abrir la base de datos");
    }
}

void insertarReto(int usuario_id, int reto_id, const char* estado) {
    char sql[128];
    sprintf(sql, "INSERT INTO retos (usuario_id, reto_id, estado) VALUES (%d, %d, '%s');", usuario_id, reto_id, estado);
    char* errMsg;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        Serial.print("Error al insertar datos: ");
        Serial.println(errMsg);
        sqlite3_free(errMsg);
    } else {
        Serial.println("Datos insertados correctamente");
    }
}

void instertar_persona(const char *full_name, const char *email, const char *department, int rank) {
    char sql[128];
    sprintf(sql, "INSERT INTO usuarios (full_name, email, department, rank) VALUES ('%s', '%s', '%s', %d);", full_name, email, department, rank);
    char* errMsg;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        Serial.print("Error al insertar datos: ");
        Serial.println(errMsg);
        sqlite3_free(errMsg);
    } else {
        Serial.println("Datos insertados correctamente");
    }
}

void insertar_skill(const char *skill){
    char sql[128];
    sprintf(sql, "INSERT INTO skill (skill) VALUES ('%s');", skill);
    char* errMsg;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK){
        Serial.print("Error al insertar datos: ");
        Serial.println(errMsg);
        sqlite3_free(errMsg);
    } else {
        Serial.println("Datos insertados correctamente");
    }
}

void get_user_skills(const char *full_name) {
    char sql[256];
    sprintf(sql, 
        "SELECT s.skill_name FROM skills s "
        "JOIN usuario_skills us ON s.id = us.skill_id "
        "JOIN usuarios u ON u.id = us.user_id "
        "WHERE u.full_name = '%s';", 
        full_name);

    Serial.println(sql);  // Para depuración, imprime la consulta generada
}

void get_users_by_skill(const char *skill_name) {
    char sql[256];
    sprintf(sql, 
        "SELECT u.full_name, us.experience FROM usuarios u "
        "JOIN usuario_skills us ON u.id = us.user_id "
        "JOIN skills s ON s.id = us.skill_id "
        "WHERE s.skill_name = '%s';", 
        skill_name);

    Serial.println(sql);  // Para depuración, imprime la consulta generada
}
