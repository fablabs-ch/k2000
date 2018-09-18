import {Component, OnInit} from '@angular/core';
import {Cocktail, CocktailItem} from '../cocktail-item/cocktail-item.component';


export const COCKTAILS_LIST: Cocktail[] = [
	new Cocktail('cocktail1', 'https://www.maliburumdrinks.com/globalassets/images/cocktail-recipe-images/malibu-island-cosmo.png/CocktailHero', [
		new CocktailItem(0, 100),
		new CocktailItem(1, 100)
	]),
	new Cocktail('cocktail2', 'http://i.f1g.fr/media/ext/1900x1900/madame.lefigaro.fr/sites/default/files/img/2017/12/cocktail-vodka-thym--pamplemousse.jpg', [
		new CocktailItem(1, 100),
		new CocktailItem(0, 100),
		new CocktailItem(1, 100)
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
