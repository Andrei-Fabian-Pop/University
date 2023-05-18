import {Recipe} from "./recipe";
import {Ingredient} from "./ingredient";

export interface Instruction {
  id?: number,
  recipe: Recipe | number,
  ingredient: Ingredient | number,
  amount: number
}
