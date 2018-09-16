import {Injectable} from '@angular/core';
import {Observable, Observer, Subject} from 'rxjs';

@Injectable({
	providedIn: 'root'
})
export class WebsocketService {

	// TODO configurable
	public static readonly URL: string = 'ws://nuc1.sabrina.gaetan:1234';

	private ws: WebSocket;

	private _onMessageSubject: Subject<MessageEvent>;

	constructor() {
		this._onMessageSubject = new Subject();
		this.connect();
	}

	public get onMessageSubject(): Subject<MessageEvent> {
		return this._onMessageSubject;
	}

	public sendCommand(cmd: string) {
		this.ws.send(`${cmd}\n`);
	}

	protected connect() {
		this.ws = new WebSocket(WebsocketService.URL);
		this.ws.onmessage = this.onMessage.bind(this);
		this.ws.onerror = this.onError.bind(this);
		this.ws.onclose = this.onClose.bind(this);
	}

	private onMessage(msg: MessageEvent) {
		this._onMessageSubject.next(msg);
	}

	private onError(event: Event) {
		console.error(`Error with websocket`, event);
	}

	private onClose(event: CloseEvent) {
		console.warn(`websocket closed`, event);
		// todo reconnect automatically
	}
}
