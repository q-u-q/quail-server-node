const { QuailServer: QuailServerInternal } = require('../build/Debug/quail-js')

class QuailServer {
  constructor() {
    this.internal = new QuailServerInternal();
  }


}