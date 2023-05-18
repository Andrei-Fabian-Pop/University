import { ComponentFixture, TestBed } from '@angular/core/testing';

import { RecipeShowComponent } from './recipe-show.component';

describe('RecipeShowComponent', () => {
  let component: RecipeShowComponent;
  let fixture: ComponentFixture<RecipeShowComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [RecipeShowComponent]
    });
    fixture = TestBed.createComponent(RecipeShowComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
