import {Component, OnInit} from '@angular/core';
import {CommunicationService, Status} from '../services/communication.service';
import {distinctUntilChanged, distinctUntilKeyChanged, filter, map} from 'rxjs/operators';

@Component({
	selector: 'app-controls',
	templateUrl: './controls.component.html',
	styleUrls: ['./controls.component.css']
})
export class ControlsComponent implements OnInit {

	public distMm = 0;

	constructor(private _communicationService: CommunicationService) {
	}

	ngOnInit() {
		console.log('init called');
		this._communicationService.status
			.pipe(
				filter(s => !!s),
				map(s => s.position),
				distinctUntilChanged()
			).subscribe((dist: number) => {
			this.distMm = dist;
		});
	}

	public home() {
		this._communicationService.home();
	}

	public emergency() {
		this._communicationService.emergency();
	}

	public release() {
		this._communicationService.release();
	}

	public clear() {
		this._communicationService.clear();
	}

	public move(distMm: number) {
		this._communicationService.move(distMm);
	}


}
