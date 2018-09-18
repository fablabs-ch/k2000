import {Injectable} from '@angular/core';
import {BehaviorSubject, Subject} from 'rxjs';
import {WebsocketService} from './websocket.service';

export class Status {
	constructor(private _fps: number, private _queueSize: number, private _position: number, private _pression: number,
				private _weight: number) {
	}

	get fps(): number {
		return this._fps;
	}

	get queueSize(): number {
		return this._queueSize;
	}

	get position(): number {
		return this._position;
	}

	get pression(): number {
		return this._pression;
	}

	get weight(): number {
		return this._weight;
	}
}

@Injectable({
	providedIn: 'root'
})
export class CommunicationService {

	private _status: BehaviorSubject<Status>;

	private _websocketSubject: Subject<MessageEvent>;

	constructor(private websocketService: WebsocketService) {
		this._status = new BehaviorSubject(null);

		this.websocketService.onMessageSubject
			.subscribe((response: MessageEvent) => {
				const split = response.data.split(':');
				// console.log('status received', split.length);
				if (split[0] === 's') {
					if (split.length === 6) {
						this._status.next(new Status(
							parseInt(split[1], 10),
							parseInt(split[2], 10),
							parseInt(split[3], 10),
							parseInt(split[4], 10),
							parseInt(split[5], 10)
						));
					} else {
						console.error(`Wrong status format`, response.data);
					}
				} else if (split[0] === 'e') {
					console.warn(`Error message received`, response.data);
				} else if (split[0] === 'i') {
					console.log(`Info received`, response.data);
				} else {
					console.log(`Unknown message `, response.data);
				}
			});
	}

	get status(): BehaviorSubject<Status> {
		return this._status;
	}

	public home() {
		this.websocketService.sendCommand('h');
	}

	public tare() {
		this.websocketService.sendCommand('t');
	}

	public emergency() {
		this.websocketService.sendCommand('e');
	}

	public release() {
		this.websocketService.sendCommand('r');
	}

	public move(distMm: number) {
		this.websocketService.sendCommand(`m:${distMm}`);
	}

	public queue(servo: number, weightGr: number) {
		this.websocketService.sendCommand(`q:${servo}:${weightGr}`);
	}

	public clear() {
		this.websocketService.sendCommand('c');
	}

	public start() {
		this.websocketService.sendCommand('s');
	}

	public aperture(servo: number, percent: number) {
		this.websocketService.sendCommand(`a:${servo}:${percent}`);
	}
}
