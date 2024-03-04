const { QuailServer } = require('..')

const cert = "/root/quail-server/certificates/certificate.pem";
const key = "/root/quail-server/certificates/certificate.key";

const server = new QuailServer();
// server.SetCallback(function(transport){
//   transport.SetCallback(function(stream_id, message){
//     console.log(`js get stream_id:${stream_id}, message:${message}`);
//     transport.Send(stream_id, "ojbk!");
//   });
// });
server.SetCallback();
server.On("/echo", function (transport) {
  transport.SetCallback(function (stream_id, message) {
    console.log(`js get stream_id:${stream_id}, message:${message}`);
    transport.Send(stream_id, "ojbk!");
  });
})

server.On("/test", function (transport) {
  transport.SetCallback(function (stream_id, message) {
    console.log(`js get stream_id:${stream_id}, message:${message}`);
    transport.Send(stream_id, "shit!");
  });
})

server.Start(cert, key);
