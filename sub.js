const mqtt = require('mqtt')
const mysql=require('mysql')

const db = mysql.createConnection({
    host: "localhost",
    port: 3306,
    user: 'root',
    password:'',
    database: 'mqttnode'
})
db.connect(() =>{
    console.log('Database ok!')
})
const sub = mqtt.connect('mqtt://localhost:9000')
sub.on('connect', ()=>{
    sub.subscribe('topic test')
})
sub.on('message',(topic,message) =>{
    message= message.toString()
    message= message.split(' ')
    const message1 = parseInt(message[1])
    const message2 = parseInt(message[0])
    console.log(message)

    db.query(
        'insert into arduino set ?',
        { data: message1, temperatura: message2 },
        (err, rows) => {
            if(!err) console.log('data saved!')
        }
    )
})
//broker.on('published', (packet) =>{
 //   console.log(packet.payload.toString())
//})