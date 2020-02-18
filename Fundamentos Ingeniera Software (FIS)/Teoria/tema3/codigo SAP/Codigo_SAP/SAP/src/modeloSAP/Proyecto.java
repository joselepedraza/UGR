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
class Proyecto {
    private String titulo;
    private int numAlumnos;
    private String descripcion;
    private Profesor miProfesor;
    private List<Asignatura> asignaturasRecomendadas= new ArrayList();
    
    Proyecto(String tit, int numAlum, String descrip, Profesor profe, List<Asignatura> asigs){
        titulo = tit;
        numAlumnos=numAlum;
        descripcion = descrip;
        asignaturasRecomendadas = asigs;
        miProfesor = profe;  
    }   
}
