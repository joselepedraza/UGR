const { isMainThread } = require("worker_threads");

const SmartContractTravel = artifacts.require("./SmartContractTravel.sol");

contract("SmartContractTravel", accounts => {
    it("El numero de pasajeros debe ser 0 al iniciar el contrato", async () => {
        const smartContractTravel = await SmartContractTravel.deployed({from: accounts[0]});    //desplegamos el contrato con la primera direccion de la lsita
        const n_pasajero = await smartContractTravel.n_pasajero({from: accounts[0]});

        assert.equal(n_pasajero, 0);
    });

    //Si añadimos un pasajero y el contador n_pasajero no incrementa...
    it("El numero de pasajeros debe ser 1 al registrar un pasajero", async () => {
        const smartContractTravel = await SmartContractTravel.deployed();
        
        const dir_csanitario = accounts[1]; //seteamos la direccion del centro sanitario a la segunda direccion de la lista

        await smartContractTravel.Registrar_datos_pasajero("Juan","Garcia Lopez","111111111X","111111111","Centro1", dir_csanitario, "NEGATIVO", {from: accounts[1]});

        const n_pasajero = await smartContractTravel.n_pasajero({from: accounts[0]});

        assert.equal(n_pasajero, 1);
    });

    //Si añadimos un pasajero y la direccion introducida por parametros no coincide con la que llama a la funcion y el error es distinto al esperado o no hay error...
    it("La direccion que llama a la funcion 'Registrar_datos_pasajero' coincide siempre con la dirección introducida por parametros", async () => {
        const smartContractTravel = await SmartContractTravel.deployed();
    
        const dir_csanitario = accounts[1]; //seteamos la direccion del centro sanitario a la segunda direccion de la lista
        const dir_aerolinea = accounts[0];
        
        try {
            await smartContractTravel.Registrar_datos_pasajero("Juan","Garcia Lopez","111111111X","111111111","Centro1", dir_csanitario, "NEGATIVO", {from: dir_aerolinea});
        } catch (e) {
            assert.equal(e, "Error: Returned error: VM Exception while processing transaction: revert La direccion introducida no coincide con el centro sanitario que envia la transaccion -- Reason given: La direccion introducida no coincide con el centro sanitario que envia la transaccion.");
        }

    });

    //Si modificamos un pasajero y la direccion introducida por parametros no coincide con la que llama a la funcion y el error es distinto al esperado o no hay error...
    it("La direccion que llama a la funcion 'Registrar_cambio_test' coincide siempre con la dirección introducida por parametros", async () => {
        const smartContractTravel = await SmartContractTravel.deployed();
    
        const dir_csanitario = accounts[1]; //seteamos la direccion del centro sanitario a la segunda direccion de la lista
        const dir_aerolinea = accounts[0];
        
        try {
            await smartContractTravel.Registrar_datos_pasajero("Juan","Garcia Lopez","111111111X","111111111","Centro1", dir_csanitario, "NEGATIVO", {from: dir_aerolinea});      
            await smartContractTravel.Registrar_cambio_test(1, dir_csanitario, {from: dir_aerolinea});
        } catch (e) {
            assert.equal(e, "Error: Returned error: VM Exception while processing transaction: revert La direccion introducida no coincide con el centro sanitario que envia la transaccion -- Reason given: La direccion introducida no coincide con el centro sanitario que envia la transaccion.");
        }

    }); 

    //Si la dirección que crea el contrato es distinta a la que llama a Datos_Pasajero_Registrado(uint _id) y el error es distinto al esperado o no hay error...
    it("La direccion que llama a la funcion 'Datos_Pasajero_Registrado' coincide siempre con la dirección creadora del contrato", async () => {
        const smartContractTravel = await SmartContractTravel.deployed({from: accounts[0]});
    
        const dir_csanitario = accounts[1]; //seteamos la direccion del centro sanitario a la segunda direccion de la lista
        //si salta la excepción es porque la direccion no coincide y lanza el error correspondiente 
        try {
            await smartContractTravel.Datos_Pasajero_Registrado(0, {from: dir_csanitario});
        } catch (e) {
            assert.equal(e, "Error: Returned error: VM Exception while processing transaction: revert Solo la aerolinea puede realizar esta funcion");
        }

    }); 

    //Si modificamos el resultado del test covid y al consultar los datos del pasajero no ha cambiado
    it("El resultado del test covid asociado al id del pasajero siempre cambia correctamente al llamar a la función 'Registrar_cambio_test'", async () => {
        const smartContractTravel = await SmartContractTravel.deployed();
      
        const dir_csanitario = accounts[1]; //seteamos la direccion del centro sanitario a la segunda direccion de la lista
        const dir_aerolinea = accounts[0];
        
            
        await smartContractTravel.Registrar_datos_pasajero("Juan","Garcia Lopez","111111111X","111111111","Centro1", dir_csanitario, "NEGATIVO", {from: dir_csanitario});      
        await smartContractTravel.Registrar_cambio_test(1, dir_csanitario, {from: dir_csanitario});
        //const result = null;
        await smartContractTravel.Datos_Pasajero_Registrado(1, {from: dir_aerolinea}).then(function(result){
            assert.equal(result[6], "POSITIVO");
        });
    }); 

    //Si la dirección que crea el contrato es distinta a la que llama a Datos_Pasajero_Registrado(uint _id) y el error es distinto al esperado o no hay error...
    it("La direccion que llama a la funcion 'destroy' coincide siempre con la dirección creadora del contrato", async () => {
        const smartContractTravel = await SmartContractTravel.deployed({from: accounts[0]});
    
        const dir_csanitario = accounts[1]; //seteamos la direccion del centro sanitario a la segunda direccion de la lista
        //si salta la excepción es porque la direccion no coincide y lanza el error correspondiente 
        try {
            await smartContractTravel.destroy({from: dir_csanitario});
        } catch (e) {
            assert.equal(e, "Error: Returned error: VM Exception while processing transaction: revert Solo la aerolinea puede realizar esta funcion -- Reason given: Solo la aerolinea puede realizar esta funcion.");
        }

    }); 





});