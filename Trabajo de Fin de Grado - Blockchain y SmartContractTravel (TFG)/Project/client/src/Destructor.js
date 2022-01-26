import React, { Component } from "react";
import './App.css';

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

class Destructor extends Component {
    constructor(props){
        super(props);
        this.state = {
            enviando: false,
            transactionHash: false
        }
        
        this._handleDestroy = this._handleDestroy.bind(this);
    }

    
    _handleDestroy(){
        /*
            Aqui se llama a la función destroyContract()
        */
       
        
        this.setState({enviando: true, transactionHash:null});
 
        //solicitamos acceso a la billetera de Metamask
        window.ethereum.enable().then(accounts => {
            const web3 = new Web3(window.ethereum);
            const smartContractTravel = new web3.eth.Contract(abi, contractAddress);
    
            smartContractTravel.methods.destroy().send({from:accounts[0]}) //accounts[0] será la direccion que llama a la función
            .on('transactionHash', transactionHash => this.setState({transactionHash}))   //primer paso para la transaccion: cuando se envia la transaccion, recuperamos el hash de la misma antes de que se mine/confirme
            .on('receipt', _ => this.setState({enviando: false}));  //segundo paso: ya se ha minado la transacción anterior, por lo que recuperamos el recibo de que se ha minado correctamente y habilitamos el boton de nuevo por si necesitamos registrar otro pasajero
        });
    }

    render(){
        const{enviando,transactionHash} = this.state;
        return(
            <div className="Container registrar-pasajero">
                <div className="destructor">
                    <button onClick={this._handleDestroy.bind(this)} disabled={enviando}>Destruir contrato</button>  
                </div>
                <span><hr />
                    <label>TransactionHash: {transactionHash}</label>
                </span>
            </div>
        );
    }
}

export default Destructor;