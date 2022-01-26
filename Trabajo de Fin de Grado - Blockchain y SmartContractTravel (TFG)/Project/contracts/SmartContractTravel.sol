// SPDX-License-Identifier: GPL-3.0

 pragma solidity >= 0.7.00 < 0.8.0; 
 
 contract Owned{
     constructor(){
         owner = msg.sender;
     }
     
     address payable owner;
     
     modifier onlyOwner{
         require(msg.sender == owner, "Solo la aerolinea puede realizar esta funcion");
         _;
     }
     
 }
 
 contract SmartContractTravel is Owned{
    
    struct Pasajero{
        string nombre;
        string apellidos;
        string dni;
        
        string nif_csanitario;
        string nombre_csanitario;
        address dir_csanitario;
        
        string resultado_test;
        
        uint id_npasajero;
    }
    
    uint public n_pasajero = 0;
    
    mapping(uint=>Pasajero) private Pasajeros;
    
    //funcion para que el centro sanitario registre los datos de los pasajeros, incluyendo resultado de la prueba Covid19
    function Registrar_datos_pasajero(string calldata _nombre, string calldata _apellidos, string calldata _dni, string calldata _nif_csanitario, string calldata _nombre_csanitario, 
        address _dir_csanitario, string calldata _resultado_test) public{
   
        n_pasajero++;
        
        Register(_nombre, _apellidos, _dni, _nif_csanitario, _nombre_csanitario, _dir_csanitario, _resultado_test, n_pasajero);
        
     
    }
    
    function Register(string calldata _nombre, string calldata _apellidos, string calldata _dni, string calldata _nif_csanitario, string calldata _nombre_csanitario,
        address _dir_csanitario, string calldata _resultado_test, uint _i) internal {
        
        require(msg.sender == _dir_csanitario, "La direccion introducida no coincide con el centro sanitario que envia la transaccion"); //requiere que el que registra los datos del pasajero sea el centro sanitario que llama al contrato

        Pasajeros[_i] = Pasajero({
            nombre: _nombre,
            apellidos: _apellidos,
            dni: _dni,
            
            nif_csanitario: _nif_csanitario,
            nombre_csanitario: _nombre_csanitario,
            dir_csanitario: _dir_csanitario,    //dir_csanitario: msg.sender,
            
            resultado_test: _resultado_test,
            
            id_npasajero: _i
        });
        
    }
    
    function Registrar_cambio_test(uint _id_npasajero, address _dir_csanitario) public{
        
        require(msg.sender == _dir_csanitario, "La direccion introducida no coincide con el centro sanitario que envia la transaccion"); //requiere que el que registra los datos del pasajero sea el centro sanitario que llama al contrato
        
        Pasajeros[_id_npasajero].resultado_test = "POSITIVO";
        
    }
    
    //funcion que solo podrá ser llamada por la aerolínea para recuperar los datos de los pasajeros
    function Datos_Pasajero_Registrado(uint _id) public onlyOwner view 
        returns (string memory nombre, string memory, string memory, string memory, string memory, address dir_csanitario, string memory, uint id_npasajero){
        
        //copiamos los datos a memoria
        Pasajero memory p = Pasajeros[_id];
        
        //devolvemos los datos del struct por separado, dado que no se pueden devolver structs (así es como actúa el compilador cuando tiene que devolver por ejemplo un mapping publico de structs, con el metodo automatico get)
        return (p.nombre, p.apellidos, p.dni, p.nif_csanitario,p.nombre_csanitario,p.dir_csanitario, p.resultado_test,p.id_npasajero);

    }
    
    //funcion para borrar permanentemente el contrato una vez que el vuelo se haya realizado (solo puede llamarla la aerolínea con la dirección que creó el contrato)
    function destroy() public onlyOwner{
        selfdestruct(owner);
    }

 }