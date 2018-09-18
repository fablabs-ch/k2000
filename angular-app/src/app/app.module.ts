import {BrowserModule} from '@angular/platform-browser';
import {NgModule} from '@angular/core';

import {AppComponent} from './app.component';
import {BrowserAnimationsModule} from '@angular/platform-browser/animations';
import {BarStatusComponent} from './bar-status/bar-status.component';
import {ControlsComponent} from './controls/controls.component';
import {MatButtonModule, MatCardModule, MatExpansionModule, MatFormFieldModule, MatInputModule, MatSliderModule} from '@angular/material';
import { CocktailListComponent } from './cocktail-list/cocktail-list.component';
import { CocktailItemComponent } from './cocktail-item/cocktail-item.component';

@NgModule({
	declarations: [
		AppComponent,
		BarStatusComponent,
		ControlsComponent,
		CocktailListComponent,
		CocktailItemComponent
	],
	imports: [
		BrowserModule,
		BrowserAnimationsModule,

		MatButtonModule,
		MatInputModule,
		MatFormFieldModule,
		MatSliderModule,
		MatExpansionModule,
		MatCardModule
	],
	providers: [],
	bootstrap: [AppComponent]
})
export class AppModule {
}
