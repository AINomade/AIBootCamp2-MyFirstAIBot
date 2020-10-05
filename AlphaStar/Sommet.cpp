#include "Sommet.h"

Sommet::Sommet() {};
Sommet::Sommet(int id, STileInfo info) :_id(id), _info(info) {}

void Sommet::AddSuivant(vector<Sommet> sommets, SInitData turnData) {
	vector<int> suivant;
	vector<pair<Sommet, Sommet>> listMurs;
	for (int i = 0; i < turnData.objectInfoArraySize; i++) {
		SObjectInfo mur = turnData.objectInfoArray[i];
		Sommet a;
		Sommet b;
		int qb, rb;
		for_each(sommets.begin(), sommets.end(), [&](const Sommet s) {
			if (s._info.q == mur.q && s._info.r == mur.r) a = s;
			});
		switch (mur.cellPosition) {
			case NW :
				qb = a._info.q-1;
				rb = a._info.r ;
				break;
			case W:
				qb = a._info.q ;
				rb = a._info.r-1;
				break;
			case SW:
				qb = a._info.q + 1;
				rb = a._info.r -1;
				break;
			case SE:
				qb = a._info.q+1;
				rb = a._info.r ;
				break;
			case E:
				qb = a._info.q ;
				rb = a._info.r+1;
				break;
			case NE:
				qb = a._info.q - 1;
				rb = a._info.r + 1;
				break;
		}
		for_each(sommets.begin(), sommets.end(), [&](const Sommet s) {
			if (s._info.q == qb && s._info.r == rb) b = s;
		});
		listMurs.push_back(make_pair(a, b));
	}

	vector<Sommet> sommetsInterdisMur;
	for_each(listMurs.begin(), listMurs.end(), [&](pair<Sommet, Sommet> pair) {
		if (pair.first == *this) sommetsInterdisMur.push_back(pair.second);
		if (pair.second == *this) sommetsInterdisMur.push_back(pair.first);
		});

	for (int j = 0; j < sommets.size(); j++) {
		int q2 = sommets[j]._info.q;
		int r2 = sommets[j]._info.r;
		
		
		bool isSommetInterdit = false;
		for_each(sommetsInterdisMur.begin(), sommetsInterdisMur.end(), [&](const Sommet sInterdit) {
			if (sInterdit._info.q == q2 && sInterdit._info.r == r2)isSommetInterdit = true;
			});

		if ((q2 == _info.q - 1 && r2 == _info.r || q2 == _info.q && r2 == _info.r || 
			q2 == _info.q && r2 == _info.r - 1 || q2 == _info.q + 1 && r2 == _info.r - 1 ||
			q2 == _info.q + 1 && r2 == _info.r || q2 == _info.q && r2 == _info.r + 1 || 
			q2 == _info.q - 1 && r2 == _info.r + 1) 
			&& sommets[j]._info.type != 1
			&& !isSommetInterdit) {
			suivant.push_back(sommets[j]._id);
		}
	}
	_suivant = suivant;

}

int Sommet::Distance2(Sommet goal) const {
	return sqrt((_info.q - goal._info.q) * (_info.q - goal._info.q) + (_info.r - goal._info.r) * (_info.r - goal._info.r));
}

int Sommet::EvaluationAStar(Sommet goal, int score) {
	return (score + Distance2(goal) + 1);
}

string Sommet::ToString() const {
	string sommettext;
	sommettext = "id : " + to_string(_id) + " coordonnées : " + to_string(_info.q) + " , " + to_string(_info.r) + " type : " + to_string(_info.type) + "\n" + "ID Suivants : ";
	for_each(_suivant.begin(), _suivant.end(), [&](const int suivant) {
		sommettext += to_string(suivant) + "  ";
		});
	return sommettext + "\n";
}

vector<int> Sommet::GetVoisins() {
	return _suivant;
}

bool Sommet::operator==(Sommet const& a)
{
	return a._id == _id;
}
