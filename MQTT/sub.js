//código para suscripción y subida de datos
const mqtt = require('mqtt')
const mysql=require('mysql')

const db = mysql.createConnection({     //parámetros la base de datos mysql
    host: "localhost",                  //se encuentra en la línea local
    port: 3306,
    user: 'root',                      
    password:'',                         
    database: 'mqttnode'                //nombre de la base de datos
})
db.connect(() =>{                        //conexión a la base de datos
    console.log('Database ok!')
})
const sub = mqtt.connect('mqtt://localhost:9000')       //suscripción al borker
sub.on('connect', ()=>{
    sub.subscribe('topic test')                          //suscripción al tema 'topic test'
})
sub.on('message',(topic,message) =>{                     //recepción del mensaje
    message= message.toString()                          //conversión del mensaje a strig
    message= message.split(' ')                          //separo en dos partes el mensaje
    const message1 = parseInt(message[1])                //guardo la sugunda parte del mensaje
    const message2 = parseInt(message[0])                //guardo la primera parte
    console.log(message)

    db.query(
        'insert into arduino set ?',
        { data: message1, temperatura: message2 },
        (err, rows) => {
            if(!err) console.log('data saved!')
        }
    )
})
 
