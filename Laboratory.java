import java.util.ArrayList;

public class Laboratory {
  private String name;
  private ArrayList<Student> students;
  private ArrayList<Professor> professors;

  public Laboratory() {
  }

  public Laboratory(String name) {
    this.name = name;
    this.students = new ArrayList<Student>();
    this.professors = new ArrayList<Professor>();
  }

  public String getName() {
    return this.name;
  }

  public void setName(String name) {
    this.name = name;
  }

  public void addMember(Student s) {
    this.students.add(s);
  }

  public void addMember(Professor p) {
    this.professors.add(p);
  }
  
  public ArrayList<String> getContactInfos() {
    // COMPLETE-ME
    // Construa um ArrayList<String> contendo informações de contato (ContactInfo)
    // de cada um dos estudantes e professores
    ArrayList<String> list = new ArrayList<String>();
    for(Student stu:this.students) {
    	list.add(stu.getContactInfo());
    }
    for(Professor prf:this.professors) {
    	list.add(prf.getContactInfo());
    }
    return list;
  }

  public boolean userExists(String userId) {
    // COMPLETE-ME
    // Verifique se existe o userId na lista de estudantes ou de professores
	  for(Student stu:this.students) {
		  if(userId == stu.getUserId()) {
			  return true;
		  }
	  }
	  for(Professor prf:this.professors) {
		  if(userId == prf.getUserId()) {
			  return true;
		  }
	  }
	  return false;
    
  }

  public int countMembers() {
    // COMPLETE-ME
    // Retorne o total de membros do laboratório (estudantes e professores)
	 return (this.students.size() + this.professors.size());
	  
  }

  /*
  Saida =  NCC has 3 members
[{class='Student', name='Nome1 Sobrenome1', userId='username1'}, {class='Student', name='Nome2 Sobrenome2', userId='username2'}, {class='Professor', name='Andrea Charao', userId='andrea', room='376', building='Anexo B'}]
User andrea found
 
 Resp = NCC has 3 members
[{class='Student', name='Nome1 Sobrenome1', userId='username1'}, {class='Student', name='Nome2 Sobrenome2', userId='username2'}, {class='Professor', name='Andrea Charao', userId='andrea', room='376', building='Anexo B'}]
User andrea found
 
   * */
  
  
}