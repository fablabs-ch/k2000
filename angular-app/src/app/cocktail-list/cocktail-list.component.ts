import {Component, OnInit} from '@angular/core';
import {Cocktail, CocktailItem} from '../cocktail-item/cocktail-item.component';


export const COCKTAILS_LIST: Cocktail[] = [
	new Cocktail('cocktail1', '70cl',
		'https://www.maliburumdrinks.com/globalassets/images/cocktail-recipe-images/malibu-island-cosmo.png/CocktailHero', [
		new CocktailItem(0, 50),
		new CocktailItem(1, 20)
	]),
	new Cocktail('cocktail2', '110cl',
		'http://i.f1g.fr/media/ext/1900x1900/madame.lefigaro.fr/sites/default/files/img/2017/12/cocktail-vodka-thym--pamplemousse.jpg', [
			new CocktailItem(1, 20),
			new CocktailItem(0, 60),
			new CocktailItem(1, 30)
		]),
	new Cocktail('cocktail', '230cl',
		'https://az826390.vo.msecnd.net/cdn/media/home/inspiring_recipes/recipes/new_-_c/cocktail-melon-miel-et-concombre-1160x650-bs007548--pub-67290-01.ashx?la=fr&mw=1160&w=1160&hash=7C2118A37A34E66FF25FC1145F6D5B76AED9F6AB', [
			new CocktailItem(0, 100),
			new CocktailItem(1, 50),
			new CocktailItem(0, 100)
		]),
];

@Component({
	selector: 'app-cocktail-list',
	templateUrl: './cocktail-list.component.html',
	styleUrls: ['./cocktail-list.component.css']
})
export class CocktailListComponent implements OnInit {


	public list: Cocktail[] = COCKTAILS_LIST;

	constructor() {
	}

	ngOnInit() {
	}

}
