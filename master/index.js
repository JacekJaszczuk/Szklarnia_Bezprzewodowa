const config = require('./config');
const express = require('express');
const datetime = require('node-datetime');
const sqlite3 = require('sqlite3').verbose();
const app = express();
const port = config.port;

var totalSlaves = 0;

var db = new sqlite3.Database(config.dbPath, sqlite3.OPEN_READWRITE, (err) => {
    let query = `SELECT id, name_flower FROM slave;`;
    
    if (err) {
        return console.error(err.message);
    }
    
    console.log(`Connected to the database: ${config.dbPath}`);

    db.all(query, [], (err, rows) => {
        if (err) {
            return console.error(err.message);
        }
        console.log("Available flowers: ");
        rows.forEach(row => {
            console.log(`${row.id}. ${row.name_flower}`);
            totalSlaves++;
        });
    });

});

var insertIntoDb = function(id, val) {

    let query;

    if (id <= 0 || id > totalSlaves) {  // sqlite assigns indexes from 1
        return console.error("Incorrect slave id.");
    }

    if (val < 0 || val > 1023) {
        return console.error(`Incorrect value provided: ${val}. Must be non-negative and smaller than 1024.`);
    }

    val = (val / 1023) * 100;
    query = `INSERT INTO measurement (slave_id, measurement, timestamp) VALUES (${id}, ${val}, datetime());`;
    
    console.log(query);

    db.run(query, function(err) {
        if (err) {
            return console.error(err.message);
        }
        console.log(`Added a row with id: ${this.lastID}.`);
    });
}

app.get('/', (request, response) => {
    response.send('App running.');
});

app.get('/data', (req, res) => {
    var id = req.query.id;
    var val = req.query.value;
    var date = datetime.create().format('Y-m-d H:M:S');
    insertIntoDb(id, val, date);
    res.status(200).send();
});

app.listen(port, (err) => {
    if (err) {
        return console.log('An error occured.', err);
    }
    console.log(`Listening on port ${port}`);
});
