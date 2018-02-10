package ch.fablabs.fabjam.cocktail.service.serial;

import ch.fablabs.fabjam.cocktail.data.serial.SerialStatus;
import ch.fablabs.fabjam.cocktail.data.type.JmsTopic;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jms.annotation.JmsListener;
import org.springframework.stereotype.Service;
import rx.subjects.BehaviorSubject;

@Service
public class SerialService {

	@Autowired
	private SerialConnectionStarter serialConnectionStarter;

	private BehaviorSubject<Integer> weightSubject;
	private BehaviorSubject<Integer> distanceFromHomeInMm;
	private BehaviorSubject<SerialStatus> serialStatus;

	public SerialService() {
		this.weightSubject = BehaviorSubject.create(-1);
		this.distanceFromHomeInMm = BehaviorSubject.create(-1);
		this.serialStatus = BehaviorSubject.create((SerialStatus) null);
	}

	public BehaviorSubject<Integer> getWeightSubject() {
		return weightSubject;
	}

	public BehaviorSubject<Integer> getDistanceFromHomeInMm() {
		return distanceFromHomeInMm;
	}

	public BehaviorSubject<SerialStatus> getSerialStatus() {
		return serialStatus;
	}

	@JmsListener(destination = JmsTopic.SERIAL_STATUS)
	private void serialStatus(SerialStatus status) {
		this.serialStatus.onNext(status);
		this.weightSubject.onNext(status.getPayloadWeightGr());
		this.distanceFromHomeInMm.onNext(status.getCarrierDistMm());
	}
}
