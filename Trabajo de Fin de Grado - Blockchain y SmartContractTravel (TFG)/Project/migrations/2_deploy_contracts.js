var SmartContractTravel = artifacts.require("./SmartContractTravel.sol");

module.exports = function(deployer) {
  deployer.deploy(SmartContractTravel);
};


