
public class Player {

	private String name;
	private int id;
	private int point;
	
	public Player(int id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public int getPoint() {
		return point;
	}

	public void setPoint(int point) {
		this.point = point;
	}
	
	// Compare 2 players score
	public int compareScore(Player p) {
		if(this.point < p.point) return -1;
		if(this.point == p.point) return 0;
		return 1;
	}
	
	@Override
	public String toString() {
		return "[ " + name + " | Score: " + point + " ]";
	}
}
