import React, { Component } from "react";

//import Web3 from 'web3';

import NumeroPasajeros from './NumeroPasajeros';
import RegistrarPasajero from './RegistrarPasajero';
import InformacionPasajero from './InformacionPasajero';

import InformacionPasajeros from './InformacionPasajeros';

import ModificarResultadoPasajero from './ModificarResultadoPasajero';
import Destructor from './Destructor';

import './App.css';


class App extends Component {
	render(){
		return (
			<div className="App">
				<div>
					<h1>Smart Contract Travel:</h1>
				</div>
				<NumeroPasajeros></NumeroPasajeros>
        <h2>Centro sanitario:</h2>
				<RegistrarPasajero></RegistrarPasajero>
				<ModificarResultadoPasajero></ModificarResultadoPasajero>
        <h2>Aerolínea:</h2>
        <InformacionPasajero></InformacionPasajero>
        <InformacionPasajeros></InformacionPasajeros>
				<Destructor></Destructor>
			</div>
		);
	}
}

export default App;