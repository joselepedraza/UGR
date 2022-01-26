-- phpMyAdmin SQL Dump
-- version 4.8.4
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1:3306
-- Tiempo de generación: 20-06-2021 a las 16:49:48
-- Versión del servidor: 5.7.24
-- Versión de PHP: 7.2.14

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `test_pw2`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `items`
--

DROP TABLE IF EXISTS `items`;
CREATE TABLE IF NOT EXISTS `items` (
  `url_img` varchar(200) COLLATE latin1_spanish_ci NOT NULL,
  `nombre` varchar(100) COLLATE latin1_spanish_ci NOT NULL,
  `precio` int(11) NOT NULL,
  `kilometraje` int(11) NOT NULL,
  `potencia` int(11) NOT NULL,
  `anio` int(11) NOT NULL,
  `ubicacion` varchar(100) COLLATE latin1_spanish_ci NOT NULL,
  PRIMARY KEY (`url_img`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_spanish_ci;

--
-- Volcado de datos para la tabla `items`
--

INSERT INTO `items` (`url_img`, `nombre`, `precio`, `kilometraje`, `potencia`, `anio`, `ubicacion`) VALUES
('Imagenes/Catalogo/Seat_Ibiza_Copa.jpg', 'Seat Ibiza Copa', 8500, 110000, 140, 2019, 'Soria'),
('Imagenes/Catalogo/Chevrolet.jpg', 'Chevrolet Orlando x7', 8500, 175000, 120, 2018, 'Vitoria'),
('Imagenes/Catalogo/Mercedes-Venz-CLA.jpg', 'Mercedes Benz CLA', 12500, 150000, 147, 2017, 'Granada'),
('Imagenes/Catalogo/Mercedes-Benz-CLA.jpg', 'Mercedes Benz CLA Sport', 15000, 210000, 170, 2016, 'Badajoz'),
('Imagenes/Catalogo/Mini.jpg', 'Mini 3 Countryman', 9800, 95000, 140, 2020, 'Cádiz'),
('Imagenes/Catalogo/Aston_Martin_Vanquish.jpg', 'Aston Martin Vanquish', 34500, 90000, 340, 2019, 'Madrid'),
('Imagenes/Catalogo/Toyota-Prius.jpg', 'Toyota Prius Plus', 7500, 180000, 140, 2015, 'Valencia'),
('Imagenes/Catalogo/Audi.jpg', 'Audi S3 Sportback', 17500, 75000, 140, 2019, 'Zamora'),
('Imagenes/Catalogo/land-rover-defender.jpg', 'Land Rover Defender', 12500, 40000, 240, 2014, 'Jaén'),
('Imagenes/Catalogo/prueba.jpg', 'prueba', 1234, 123, 123, 1999, 'Aqui');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `secciones`
--

DROP TABLE IF EXISTS `secciones`;
CREATE TABLE IF NOT EXISTS `secciones` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nombre` varchar(18) COLLATE latin1_spanish_ci NOT NULL,
  `items` varchar(1000) COLLATE latin1_spanish_ci DEFAULT NULL,
  `titulo` varchar(50) COLLATE latin1_spanish_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=22 DEFAULT CHARSET=latin1 COLLATE=latin1_spanish_ci;

--
-- Volcado de datos para la tabla `secciones`
--

INSERT INTO `secciones` (`id`, `nombre`, `items`, `titulo`) VALUES
(5, 'index', '', 'Home'),
(8, 'seccion1', '', 'Segunda Mano'),
(13, 'seccion1', '', 'Km0');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `usuarios`
--

DROP TABLE IF EXISTS `usuarios`;
CREATE TABLE IF NOT EXISTS `usuarios` (
  `usuario` varchar(30) COLLATE latin1_spanish_ci NOT NULL,
  `password` varchar(15) COLLATE latin1_spanish_ci NOT NULL,
  `nombre` varchar(30) COLLATE latin1_spanish_ci NOT NULL,
  `apellidos` varchar(30) COLLATE latin1_spanish_ci NOT NULL,
  `email` varchar(30) COLLATE latin1_spanish_ci NOT NULL,
  `telefono` varchar(15) COLLATE latin1_spanish_ci NOT NULL,
  `nacimiento` varchar(15) COLLATE latin1_spanish_ci NOT NULL,
  `intereses` varchar(15) COLLATE latin1_spanish_ci NOT NULL,
  `conociste` varchar(30) COLLATE latin1_spanish_ci NOT NULL,
  PRIMARY KEY (`usuario`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_spanish_ci;

--
-- Volcado de datos para la tabla `usuarios`
--

INSERT INTO `usuarios` (`usuario`, `password`, `nombre`, `apellidos`, `email`, `telefono`, `nacimiento`, `intereses`, `conociste`) VALUES
('admin', 'adminadmin', 'admin', 'admin', 'admin@admin.com', '666666666', '2021-05-23', 'admin', 'admin'),
('Josele', 'joselele', 'Jose', 'Luis', 'josele@josele', '222', '1995-05-23', 'vender', 'Un amigo'),
('Mariam', 'mariammari', 'Mariam', 'Mariam', 'mariam@mariam.es', '111', '2021-06-04', 'ambas', 'Publicidad'),
('Alfredo', 'alfredoal', 'Alfredo', 'Alfredo', 'alfredo@alfredo', '444', '2021-06-05', 'vender', 'Email');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
