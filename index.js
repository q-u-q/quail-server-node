const { QuailServer: QuailServerInternal } = require('./build/Debug/quail-js')

class QuailServer {
  constructor() {
    this.internal = new QuailServerInternal();
    this.cbs = new Map();
    this.cb = (path, data) => {
      const c = this.cbs.get(path);
      c(data);
    }
  }

  Start(cert, key) {
    this.internal.Start(cert, key);
  }

  SetCallback() {
    this.internal.SetCallback(this.cb);
  }

  On(path, cb) {
    this.cbs.set(path, cb);
    this.internal.On(path);
  }

}

module.exports = {
  QuailServer,
};