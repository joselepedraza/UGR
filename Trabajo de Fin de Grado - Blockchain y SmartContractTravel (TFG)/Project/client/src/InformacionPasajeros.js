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

class InformacionPasajeros extends Component {
    constructor(props){
        super(props);
        this.state = {
            datos: new Map(),
            info_pasajero: [],
            numeroPasajeros: 0
        }

        this._renderDatos = this._renderDatos.bind(this);
        this._renderButtons = this._renderButtons.bind(this);
        this._fetchInformacion = this._fetchInformacion.bind(this);
        this._clearData = this._clearData.bind(this);

        //inicializamos el número de pasajeros
        const web3 = new Web3(nodeEndpoint);
        const smartContractTravel = new web3.eth.Contract(abi, contractAddress);
        smartContractTravel.methods.n_pasajero().call().then(numeroPasajeros => this.setState({numeroPasajeros}));
    }

    _fetchInformacion(){
            
          const {numeroPasajeros} = this.state;

          if(numeroPasajeros > 0){
            const web3 = new Web3(nodeEndpoint);
            const smartContractTravel = new web3.eth.Contract(abi, contractAddress);

            let datos = new Map();
            window.ethereum.enable().then(accounts => {
               
                  for(let id=1; id<=numeroPasajeros; id++){
                      smartContractTravel.methods.Datos_Pasajero_Registrado(id).call({from:accounts[0]}).then(function(result){
                        let info_pasajero1 = [];

                        for (let i=0; i < 7; i++){
                            info_pasajero1.push(result[i]);
                        }

                        datos.set(id,info_pasajero1);
                        
                      }).then(result => this.setState({datos: datos}));      
                  }      
              
            });
        }
         
    }

    //Esto setea a blanco/vacío los estados para limpiar el input y tal
    _clearData(){
        this.setState({
            datos: new Map()
        });
    }

    // Renderiza los botones
    _renderButtons(){
        return(
            <div className="obtener-informacion">
                <button onClick={this._fetchInformacion}>Obtener pasajeros</button>
                <button onClick={this._clearData}>Limpiar datos</button>
            </div>
        );
    }
    /*
        Una vez que datos tiene contenido, lo renderizamos aquí
        Como datos es un mapa, por cada par key-value añado a una lista
        un elemento <span></span> con la información dentro de modo
        que luego renderiza todos directamente
    */
    _renderDatos(){
        const {numeroPasajeros,datos} = this.state; //aqui tenemos los datos cargados
  
            let items=[];
            for(let [key, value] of datos){
                items.push(<span>Nombre pasajero: {value[0]}<br /></span>);
                items.push(<span>Apellidos pasajero: {value[1]}<br /></span>);
                items.push(<span>DNI pasajero: {value[2]}<br /></span>);
                items.push(<span>NIF centro sanitario: {value[3]}<br /></span>);
                items.push(<span>Nombre centro sanitario: {value[4]}<br /></span>);
                items.push(<span>Dirección centro sanitario: {value[5]}<br /></span>);
                items.push(<span>Resultado Test Covid19: {value[6]}<br /><hr /></span>);
            }
            return items;

    }

    render(){
        return(
            <div className="Container registrar-pasajero">
                <div className="pasajeroId">
                    {this._renderButtons()}
                </div>
                {this._renderDatos()}
            </div>
        );
    }
}

export default InformacionPasajeros;