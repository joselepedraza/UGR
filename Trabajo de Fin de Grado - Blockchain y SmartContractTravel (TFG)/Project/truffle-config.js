const path = require("path");

module.exports = {
  // See <http://truffleframework.com/docs/advanced/configuration>
  // to customize your Truffle configuration!
  contracts_build_directory: path.join(__dirname, "client/src/contracts"),
  networks: {
    develop: {
      host: "localhost",
      port: 8545,
      network_id: 5777,
      from: "0xb6768c994ad8bc4bfd2f0ecfd45ae864f021ef7b" // default address to use for any transaction Truffle makes during migrations
    }
  },
  compilers: {
    solc: {
      version: "0.7.6" // A version or constraint - Ex. "^0.5.0"
    }
  }
};
