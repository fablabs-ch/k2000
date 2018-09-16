import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { BarStatusComponent } from './bar-status.component';

describe('BarStatusComponent', () => {
  let component: BarStatusComponent;
  let fixture: ComponentFixture<BarStatusComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ BarStatusComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(BarStatusComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
