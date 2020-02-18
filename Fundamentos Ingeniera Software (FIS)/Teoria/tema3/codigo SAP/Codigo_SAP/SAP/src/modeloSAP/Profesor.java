/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package modeloSAP;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author aanaya
 */
class Profesor {
    private String nombre;
    private String dni; 
    private String departamento;
    private List<Proyecto> misProyectos = new ArrayList();
    
    String getDni(){
        return dni;
    }
    
    void incluirProyecto(Proyecto pro){
        misProyectos.add(pro);    
    }
    
    
}
