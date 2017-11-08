const express = require('express');
const datetime = require('node-datetime');
const app = express();
const port = 3000;

app.get('/', (request, response) => {
    response.send('App running.');
});

app.get('/data', (req, res) => {
    var id = req.query.id;
    var val = req.query.value;
    var date = datetime.create().format('Y-m-d H:M:S');
    console.log(`${date}\tSlave ${id}: ${val}`);
    res.status(200).send();
});

app.listen(port, (err) => {
    if (err) {
        return console.log('An error occured.', err);
    }
    console.log(`Listening on port ${port}`);
});
