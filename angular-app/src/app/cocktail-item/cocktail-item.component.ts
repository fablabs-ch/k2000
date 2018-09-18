import {Component, Input, OnInit} from '@angular/core';
import {CommunicationService} from '../services/communication.service';


export class CocktailItem {
	constructor(private _servo: number, private _weight: number) {
	}

	get servo(): number {
		return this._servo;
	}

	get weight(): number {
		return this._weight;
	}
}

export class Cocktail {
	constructor(private _name: string, private _image: string, private _items: CocktailItem[]) {

	}

	get name(): string {
		return this._name;
	}

	get items(): CocktailItem[] {
		return this._items;
	}

	get image(): string {
		return this._image;
	}
}

@Component({
	selector: 'app-cocktail-item',
	templateUrl: './cocktail-item.component.html',
	styleUrls: ['./cocktail-item.component.css']
})
export class CocktailItemComponent implements OnInit {

	@Input()
	public cocktail: Cocktail;

	constructor(private _communicationService: CommunicationService) {
	}

	ngOnInit() {
	}

	public drink(): void {
		this.cocktail.items.forEach((item: CocktailItem) => this._communicationService.queue(item.servo, item.weight));
		this._communicationService.start();
	}

}
