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
];


class NumeroPasajeros extends Component {
    constructor(props){
        super(props);
        this.state = {
            numeroPasajeros:0,
        }
        this.handleClick = this.handleClick.bind(this);
    }

    handleClick(){
        /*
            Aquí se llama a la función getNpasajero() y el numero de pasajeros que
            devuelve esa función se le asigna a numeroPasajeros con
            this.setState({numerosPasajeros: numero})

            Así ya directamente el número se actualiza
        */
       const web3 = new Web3(nodeEndpoint);
       //instanciamos nuestro contrato:
       const smartContractTravel = new web3.eth.Contract(abi, contractAddress);
       //ya podemos llamar a sus metodos:
       smartContractTravel.methods.n_pasajero().call().then(numeroPasajeros => this.setState({numeroPasajeros}));
    }

    render(){
        const {numeroPasajeros} = this.state;

        return(
            <div className="Container pasajeros">
                <span>Numero de Pasajeros: {numeroPasajeros}</span>
                <button onClick={this.handleClick}>Obtener Numero de pasajeros</button>
            </div>
        );
    }
}


export default NumeroPasajeros;
