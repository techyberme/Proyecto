const mosca=require('mosca')     
const broker = new mosca.Server({   //inicializo el broker en el puerto 9000
    port:9000
})
broker.on('ready',() =>{           //enciendo el broker
    console.log('Mosca broker in ready!')            //muestro en la consola que el broker se ha encendido correctamente
})

broker.on('clientConnected' , (client) =>{            //muestro en la consolo los nuevos clientes conectados
    console.log('New client' + client.id)
})
