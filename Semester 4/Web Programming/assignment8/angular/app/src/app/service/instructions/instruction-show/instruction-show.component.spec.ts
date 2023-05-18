import { ComponentFixture, TestBed } from '@angular/core/testing';

import { InstructionShowComponent } from './instruction-show.component';

describe('InstructionShowComponent', () => {
  let component: InstructionShowComponent;
  let fixture: ComponentFixture<InstructionShowComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [InstructionShowComponent]
    });
    fixture = TestBed.createComponent(InstructionShowComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
