const { QuailServer } = require('../build/Debug/quail-js')

const cert = "/root/quail-server/certificates/certificate.pem";
const key = "/root/quail-server/certificates/certificate.key";

const server = new QuailServer();
server.SetCallback(function(transport){
  transport.SetCallback(function(){

  });
});
server.Start(cert, key);
