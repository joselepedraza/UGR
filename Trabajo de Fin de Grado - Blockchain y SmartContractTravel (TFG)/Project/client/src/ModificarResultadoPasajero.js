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


class ModificarResultadoPasajero extends Component {
    constructor(props){
        super(props);
        this.state = {
            /*Aquí se pueden añadir los que queramos, si falta alguno solo tenemos que ponerlo y el
            componente lo renderiza solo*/
            nombreVariables: ['id', 'DireccionCuenta'],
            datos: new Map(),

            enviando: false,
            transactionHash: false
        }

        this._renderFields = this._renderFields.bind(this);
        this._renderButtons = this._renderButtons.bind(this);
        this._handleChange = this._handleChange.bind(this);
        this._handleClick = this._handleClick.bind(this);
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

    _handleClick(){
        /*
            Al igual que en RegistrarPasajero.js, aquí se llama a la función
            setCambioTest sacando la información de 'datos'
        */
        const {datos} = this.state;

        if(datos.get('id') <= 0 || datos.get('DireccionCuenta') == null){
            alert("Los campos no pueden estar vacíos");
        }else{
            this.setState({enviando: true, transactionHash:null});
            //solicitamos acceso a la billetera de Metamask
            window.ethereum.enable().then(accounts => {

                const web3 = new Web3(window.ethereum);
                const smartContractTravel = new web3.eth.Contract(abi, contractAddress);
        
                smartContractTravel.methods.Registrar_cambio_test(datos.get('id'), datos.get('DireccionCuenta')).send({from:accounts[0]}) //accounts[0] será la direccion que llama a la función
                .on('transactionHash', transactionHash => this.setState({transactionHash}))   //primer paso para la transaccion: cuando se envia la transaccion, recuperamos el hash de la misma antes de que se mine/confirme
                .on('receipt', _ => this.setState({enviando: false}));  //segundo paso: ya se ha minado la transacción anterior, por lo que recuperamos el recibo de que se ha minado correctamente y habilitamos el boton de nuevo por si necesitamos registrar otro pasajero
                });

        }
        

    }

    //Limpia los datos de los inputs
    _handleReset(){
        const {nombreVariables} = this.state;

        let datos = new Map();
        this.setState({datos});

        nombreVariables.forEach(value =>document.getElementById(value).value= "");

    }

    //Renderiza los inputs como en RegistrarPasajero
    _renderFields(){
        const {nombreVariables} = this.state;

        return (nombreVariables.map((value) =>
            <input className="input-informacion" type='text' id={value} placeholder={value} onChange={this._handleChange}></input>
        ));
    }

    //Renderiza los botones
    _renderButtons(){
        const{enviando} = this.state;
        return(
            <div className="Botones">
                <button className="boton" onClick={this._handleClick} disabled={enviando}> Cambiar resultado </button>
                <button onClick={this._handleReset} disabled={enviando}>Resetear datos</button>
            </div>
        );
    }

    render(){
        const{transactionHash} = this.state;
        return(
            <div className="Container registrar-pasajero">
                <div className="fields">
                    {this._renderFields()}
                </div>
                {this._renderButtons()}
                <span><br /><hr />
                    <label>TransactionHash: {transactionHash}</label>
                </span>  
            </div>
              
        );
    }
}


export default ModificarResultadoPasajero;
