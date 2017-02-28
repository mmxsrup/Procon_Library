bool is_ururu(int y){
	if(y % 4) return false;
	else if(y % 100) return true;
	else if(y % 400) return false;
	else return true;
}