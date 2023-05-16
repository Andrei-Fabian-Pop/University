import { ComponentFixture, TestBed } from '@angular/core/testing';

import { IngredientShowComponent } from './ingredient-show.component';

describe('IngredientShowComponent', () => {
  let component: IngredientShowComponent;
  let fixture: ComponentFixture<IngredientShowComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [IngredientShowComponent]
    });
    fixture = TestBed.createComponent(IngredientShowComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
