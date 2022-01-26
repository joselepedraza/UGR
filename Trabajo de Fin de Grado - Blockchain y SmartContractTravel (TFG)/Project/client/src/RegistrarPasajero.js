import './App.css';
import React, { Component } from "react";

import Web3 from 'web3';

const nodeEndpoint = 'http://127.0.0.1:8545/';
const contractAddress = '0xEF2f61dCd7BF1Bf08Ac8f86952b33c499Ae5f10D';

const abi = [
  {
    "inputs": [],
    "name": "n_pasajero",
    "outputs": [
      {
        "internalType": "uint256",
        "name": "",
        "type": "uint256"
      }
    ],
    "stateMutability": "view",
    "type": "function",
    "constant": true
  },
  {
    "inputs": [
      {
        "internalType": "string",
        "name": "_nombre",
        "type": "string"
      },
      {
        "internalType": "string",
        "name": "_apellidos",
        "type": "string"
      },
      {
        "internalType": "string",
        "name": "_dni",
        "type": "string"
      },
      {
        "internalType": "string",
        "name": "_nif_csanitario",
        "type": "string"
      },
      {
        "internalType": "string",
        "name": "_nombre_csanitario",
        "type": "string"
      },
      {
        "internalType": "address",
        "name": "_dir_csanitario",
        "type": "address"
      },
      {
        "internalType": "string",
        "name": "_resultado_test",
        "type": "string"
      }
    ],
    "name": "Registrar_datos_pasajero",
    "outputs": [],
    "stateMutability": "nonpayable",
    "type": "function"
  },
  {
    "inputs": [
      {
        "internalType": "uint256",
        "name": "_id_npasajero",
        "type": "uint256"
      },
      {
        "internalType": "address",
        "name": "_dir_csanitario",
        "type": "address"
      }
    ],
    "name": "Registrar_cambio_test",
    "outputs": [],
    "stateMutability": "nonpayable",
    "type": "function"
  },
  {
    "inputs": [
      {
        "internalType": "uint256",
        "name": "_id",
        "type": "uint256"
      }
    ],
    "name": "Datos_Pasajero_Registrado",
    "outputs": [
      {
        "internalType": "string",
        "name": "nombre",
        "type": "string"
      },
      {
        "internalType": "string",
        "name": "",
        "type": "string"
      },
      {
        "internalType": "string",
        "name": "",
        "type": "string"
      },
      {
        "internalType": "string",
        "name": "",
        "type": "string"
      },
      {
        "internalType": "string",
        "name": "",
        "type": "string"
      },
      {
        "internalType": "address",
        "name": "dir_csanitario",
        "type": "address"
      },
      {
        "internalType": "string",
        "name": "",
        "type": "string"
      },
      {
        "internalType": "uint256",
        "name": "id_npasajero",
        "type": "uint256"
      }
    ],
    "stateMutability": "view",
    "type": "function",
    "constant": true
  },
  {
    "inputs": [],
    "name": "destroy",
    "outputs": [],
    "stateMutability": "nonpayable",
    "type": "function"
  }
]


class RegistrarPasajero extends Component {
    constructor(props){
        super(props);
        this.state = {
            /*Aquí se puede añadir los que se quiera, si falta alguno solo se tiene que poner y el
            componente lo renderiza solo*/
            nombreVariables: ['Nombre', 'Apellidos','Dni','Centro','NifCentro','DireccionCuenta'],
            datos: new Map(),

            enviando: false,
            transactionHash: null,
            numeroPasajeros: null
        }

        this._renderFields = this._renderFields.bind(this);
        this._renderButtons = this._renderButtons.bind(this);
        this._handleChange = this._handleChange.bind(this);
        this._handleClick = this._handleClick.bind(this);
        this._handleResult = this._handleResult.bind(this);
        this._handleReset = this._handleReset.bind(this);
    }
    /*
        Esto maneja el cambio en cada input. Con e.target.value saca el valor
        y con el e.target.attributes.placeholder.value saca el campo al que
        corresponde
    */
    _handleChange(e){
        let {datos} = this.state;

        let value = e.target.value ;
        let variable = e.target.attributes.placeholder.value;

        datos.set(variable,value);
    }

    /*
        Con los input de tipo radio, el handle anterior no funciona tal que así,
        por el contenido de target. Por eso lo hacemos a parte, hace lo mismo que
        el anterior pero solo para el resultado
    */
    _handleResult(e){
        let {datos} = this.state;

        let value = e.target.attributes.value.nodeValue;
        let variable = e.target.attributes.name.nodeValue;

        datos.set(variable, value);
    }

    _handleClick(){
        /*
            Aquí se llama a la función setPasajero() y en esa función
            se utilizarías los datos del estado extrayendolos con
            const {datos} = this.state;

            Y despues se accede a cada uno como en un diccionario: datos.get('Nombre'), por ejemplo

        */
            const {datos} = this.state;
            
            if(datos.get('Nombre') == null || datos.get('Apellidos') == null || datos.get('Dni') == null || datos.get('Centro') == null || datos.get('NifCentro') == null || datos.get('DireccionCuenta') == null || datos.get('Resultado') == null){
                alert("Los campos no pueden estar vacíos");
            }else{
                this.setState({enviando: true, transactionHash:null});
                //solicitamos acceso a la billetera de Metamask
                window.ethereum.enable().then(accounts => {

                    const web3 = new Web3(window.ethereum);
                    const smartContractTravel = new web3.eth.Contract(abi, contractAddress);
                    
                    //si la direccion introducida por parametros no coincide con la que llama a la funcion, la transaccion fallará al firmarla en metamask, mostrando el error del contrato
                    smartContractTravel.methods.Registrar_datos_pasajero(datos.get('Nombre'), datos.get('Apellidos'),datos.get('Dni'), datos.get('Centro'),datos.get('NifCentro'), datos.get('DireccionCuenta'), datos.get('Resultado')).send({from:accounts[0]}) //accounts[0] será la direccion que llama a la función
                    .on('transactionHash', transactionHash => this.setState({transactionHash}))   //primer paso para la transaccion: cuando se envia la transaccion, recuperamos el hash de la misma antes de que se mine/confirme
                    .on('receipt', _ => this.setState({enviando: false}));  //segundo paso: ya se ha minado la transacción anterior, por lo que recuperamos el recibo de que se ha minado correctamente y habilitamos el boton de nuevo por si necesitamos registrar otro pasajero
                
                    smartContractTravel.methods.n_pasajero().call().then(numeroPasajeros => this.setState({numeroPasajeros}));
                });
            }
            

    }

    //Esta función limpia los inputs
    _handleReset(){
        const {nombreVariables} = this.state;

        let datos = new Map();
        this.setState({datos});

        nombreVariables.forEach(value =>document.getElementById(value).value= "");
    }

    //Estas funciones solo se encargan de renderizar elementos html

    _renderFields(){
        const {nombreVariables} = this.state;
        /*
            Devolvemos un input por cada valor que hay dentro de nombreVariables
            La función map hace algo para cada uno de los elementos de nombreVariables, en este caso
            itera y value coge cada vez un valor de la lista, creando un input por cada uno de los valores
        */
        return (nombreVariables.map((value) =>
            <input className="input-informacion" type='text' id={value} placeholder={value} onChange={this._handleChange}></input>
        ));
    }

    _renderResultado(){
        return(
            <div>
                <input type="radio" name="Resultado" value="Positivo" onChange={this._handleResult}/>
                <label>Positivo</label>
                <input type="radio" name="Resultado" value="Negativo" onChange={this._handleResult}/>
                <label>Negativo</label>
            </div>
        );
    }

    _renderButtons(){
        const{enviando} = this.state;
        return(
            <div className="Botones">
                <button onClick={this._handleClick} disabled={enviando}> Registrar pasajero</button>
                <button onClick={this._handleReset} disabled={enviando}>Resetear datos</button>
            </div>
        );
    }

    render(){
        let{numeroPasajeros} = this.state;
        const{transactionHash} = this.state;
        
        if(numeroPasajeros >= 0){
          numeroPasajeros++;
        }
        

        return(
            <div className="Container registrar-pasajero">
                <div className="fields">
                    {this._renderFields()}
                    {this._renderResultado()}
                </div>                
                {this._renderButtons()}   
                <span><br /><hr />Identificador del pasajero: {numeroPasajeros} </span>     
                <span><hr />
                    <label>TransactionHash: {transactionHash}</label>
                </span>      
            </div>
        );
    }
}


export default RegistrarPasajero;
