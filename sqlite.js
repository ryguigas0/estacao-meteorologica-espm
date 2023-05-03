/**
 * Module handles database management
 */

const fs = require("fs");
const dbFile = `./.data/${process.env.DB_NAME || 'estacao'}.db`;
const exists = fs.existsSync(dbFile);
const sqlite3 = require("sqlite3").verbose();
const dbWrapper = require("sqlite");
const casual = require("casual");
let db;

//SQLite wrapper for async / await connections https://www.npmjs.com/package/sqlite
if (!exists) {
  fs.mkdirSync(".data")
  fs.writeFileSync(dbFile, "")
}

dbWrapper
  .open({
    filename: dbFile,
    driver: sqlite3.Database
  })
  .then(async dBase => {
    db = dBase;

    try {
      await db.run(
        "CREATE TABLE if not exists Leituras (id INTEGER PRIMARY KEY AUTOINCREMENT, temperatura REAL, umidade REAL, data_criacao TEXT)"
      );

      // Leituras geradas para testes
      // for (let r = 0; r < 5; r++)
      //   await db.run(
      //     "INSERT INTO Leituras (temperatura, umidade, data_criacao) VALUES (?, ?, datetime('now'))",
      //     parseFloat(`${(Math.random() * 50)}`).toFixed(2),
      //     parseFloat(`${(Math.random() * 100)}`).toFixed(2),
      //   );
      // console.log(await db.all("SELECT * from Leituras"));
      
    } catch (dbError) {
      console.error(dbError);
    }
  });

// Server script calls these methods to connect to the db
module.exports = {

  // Get the Leituras in the database
  getLeituras: async () => {
    try {
      return await db.all("SELECT * from Leituras");
    } catch (dbError) {
      console.error(dbError);
    }
  },

  // Add new leitura
  addMessage: async leitura => {
    let success = false;
    try {
      success = await db.run("INSERT INTO Leituras (temperatura, umidade, data_criacao) VALUES (?, ?, datetime('now'))", [
        leitura.temperatura, leitura.umidade
      ]);
    } catch (dbError) {
      console.error(dbError);
    }
    return success.changes > 0 ? true : false;
  },

  // // Update leitura text
  // updateMessage: async (id, leitura) => {
  //   let success = false;
  //   try {
  //     success = await db.run(
  //       "Update Leituras SET leitura = ? WHERE id = ?",
  //       leitura,
  //       id
  //     );
  //   } catch (dbError) {
  //     console.error(dbError);
  //   }
  //   return success.changes > 0 ? true : false;
  // },

  // Remove leitura
  deleteMessage: async id => {
    let success = false;
    try {
      success = await db.run("Delete from Leituras WHERE id = ?", id);
    } catch (dbError) {
      console.error(dbError);
    }
    return success.changes > 0 ? true : false;
  }
};
