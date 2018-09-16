import {BrowserModule} from '@angular/platform-browser';
import {NgModule} from '@angular/core';

import {AppComponent} from './app.component';
import {BrowserAnimationsModule} from '@angular/platform-browser/animations';
import {BarStatusComponent} from './bar-status/bar-status.component';
import {ControlsComponent} from './controls/controls.component';
import {MatButtonModule, MatFormFieldModule, MatInputModule, MatSliderModule} from '@angular/material';

@NgModule({
	declarations: [
		AppComponent,
		BarStatusComponent,
		ControlsComponent
	],
	imports: [
		BrowserModule,
		BrowserAnimationsModule,

		MatButtonModule,
		MatInputModule,
		MatFormFieldModule,
		MatSliderModule
	],
	providers: [],
	bootstrap: [AppComponent]
})
export class AppModule {
}
