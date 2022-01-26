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


class InformacionPasajero extends Component {
    constructor(props){
        super(props);
        this.state = {
            id:'',
            info_pasajero: []
        }

        this._renderDatos = this._renderDatos.bind(this);
        this._renderButtons = this._renderButtons.bind(this);
        this._handleChange =this._handleChange.bind(this);
        this._fetchInformacion = this._fetchInformacion.bind(this);
        this._clearData = this._clearData.bind(this);
    }

    _handleChange(e){
        // Aquí se asigna el ID del pasajero introducido en el input
        this.setState({id:e.target.value});
    }

    _fetchInformacion(){
        /*
            Aquí se llama a la función getInfoPasajero pasandole el ID del estado con const {id} = this.state
            
            Para asegurarnos de que no hace una llamada erronea, metemos la llamada getInfoPasajero dentro de un if que compruebe si
            id tiene algo o está vacío, para evitar que haga la llamada sin que haya un id escrito
        */

        const {id} = this.state;

        if(id > 0){
          let info_pasajero1 = [];
          const web3 = new Web3(nodeEndpoint);
          const smartContractTravel = new web3.eth.Contract(abi, contractAddress);
      
          window.ethereum.enable().then(accounts => {
              smartContractTravel.methods.Datos_Pasajero_Registrado(id).call({from:accounts[0]}).then(function(result){

                  for (let i=0; i < 7; i++){
                      info_pasajero1.push(result[i]);
                  }

                  return info_pasajero1;

              }).then(result => this.setState({info_pasajero: info_pasajero1}));
          });
            
        }else{
          alert("Los campos no pueden estar vacíos");
        }

        
    }

    //Esto setea a blanco/vacío los estados para limpiar el input
    _clearData(){
        this.setState({
            id:''
            //datos: new Map()
        });
        document.getElementById('id').value= "";
    }

    //Renderiza el input del id
    _renderPasajeroId(){
        const {id} = this.state;
        return(
            <div>
                <input type="number" placeholder="Id del pasajero" id="id" value={id} onChange={this._handleChange}></input>
            </div>
        );
    }
    // Renderiza los botones
    _renderButtons(){
        return(
            <div className="obtener-informacion">
                <button onClick={this._fetchInformacion}>Obtener pasajero</button>
                <button onClick={this._clearData}>Limpiar datos</button>
            </div>
        );
    }
    /*
        Una vez que datos tiene contenido, lo renderizamos aquí
    */
    _renderDatos(){
         
      const {info_pasajero} = this.state; //cargamos los datos
      if (info_pasajero.length !== 0) {
        return (
          <div>
            <hr />
            &nbsp;&nbsp;<label> Nombre pasajero: {info_pasajero[0]} </label>  <br />
            &nbsp;&nbsp;<label> Apellidos pasajero: {info_pasajero[1]} </label> <br />
            &nbsp;&nbsp;<label> DNI pasajero: {info_pasajero[2]} </label> <br />
            &nbsp;&nbsp;<label> NIF centro sanitario: {info_pasajero[3]} </label> <br />
            &nbsp;&nbsp;<label> Nombre centro sanitario: {info_pasajero[4]} </label>  <br />
            &nbsp;&nbsp;<label> Dirección centro sanitario: {info_pasajero[5]} </label> <br />
            &nbsp;&nbsp;<label> Resultado Test Covid19: {info_pasajero[6]} </label> <br />
          </div>        
        );
      }
    }

    render(){
        return(
            <div className="Container registrar-pasajero">
                <div className="pasajeroId">
                    {this._renderPasajeroId()}
                    {this._renderButtons()}
                </div>
                {this._renderDatos()}
            </div>
        );
    }
}

export default InformacionPasajero;
