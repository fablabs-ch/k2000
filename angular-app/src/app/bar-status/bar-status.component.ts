import {Component, OnInit} from '@angular/core';
import {CommunicationService, Status} from '../services/communication.service';

@Component({
	selector: 'app-bar-status',
	templateUrl: './bar-status.component.html',
	styleUrls: ['./bar-status.component.css']
})
export class BarStatusComponent implements OnInit {

	public status: Status;

	constructor(private _communicationService: CommunicationService) {
	}

	ngOnInit() {
		// TODO unsubscribe
		this._communicationService.status.subscribe((status) => this.status = status);
	}


}
