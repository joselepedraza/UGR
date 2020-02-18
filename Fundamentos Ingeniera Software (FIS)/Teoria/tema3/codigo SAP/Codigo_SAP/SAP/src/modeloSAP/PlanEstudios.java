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
class PlanEstudios {
    private List<Asignatura> asignaturas = new ArrayList();
    
    List<Asignatura> obtenerAsignaturas(List<String> listaCodAsig){
        List<Asignatura> resultado = new ArrayList();
        for(String codAsig:listaCodAsig){
            for(Asignatura asig: asignaturas){
                if(asig.obtenerCodigo().equals(codAsig)){
                    resultado.add(asig);
                }               
            }        
        } 
        return resultado;    
    }    
}
