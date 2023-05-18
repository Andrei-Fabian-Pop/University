import {Component, OnInit} from '@angular/core';
import {Instruction} from "../../../models/instruction";
import {HttpClient} from "@angular/common/http";
import {Router} from "@angular/router";
import {Observable} from "rxjs";
import {backendUrl} from "../../../\.constants"

@Component({
    selector: 'app-instruction-show',
    templateUrl: './instruction-show.component.html',
    styleUrls: ['./instruction-show.component.css']
})

export class InstructionShowComponent implements OnInit {
    protected instructions: Array<Instruction> = [];
    protected selectedInstruction: Instruction | null = null;
    private readonly table_name = "RecipeInstructions";

    protected offset = 0;
    protected limit = 5;

    selectInstruction(Instruction: Instruction) {
        this.selectedInstruction = Instruction;
    }

    constructor(private http: HttpClient, private router: Router) {
    }

    ngOnInit(): void {
        this.pullInstructions(this.offset, this.limit);
    }

    pullInstructions(offset: number, limit: number): void {
        this.refresh(offset, limit).subscribe(Instructions => this.instructions = Instructions);
    }

    insertInstruction(recipe: string, ingredient: string, amount: string): void {
        this.http.post(backendUrl + `add.php`, {
            table_name: this.table_name,
            data: {
                recipe: recipe,
                ingredient: ingredient,
                amount: amount
            }
        }).subscribe((result) => {
            console.log(result);
        });
    }

    updateInstruction(recipe: string, ingredient: string, amount: string): void {
        if (recipe == null) {
            alert("missing recipe field");
            return;
        }
        if (ingredient == null) {
            alert("missing ingredient field");
            return;
        }
        if (amount == null) {
            alert("missing amount field");
            return;
        }
        this.http.patch(backendUrl + `update.php`, {
            table_name: this.table_name,
            id: this.selectedInstruction?.id,
            data: {
                recipe: recipe,
                ingredient: ingredient,
                amount: amount
            }
        }).subscribe((result) => {
            console.log(result);
            this.pullInstructions(this.offset, this.limit);
        });
    }

    deleteInstruction(): void {
        let id_to_send;
        if (this.selectedInstruction?.id !== undefined) {
            id_to_send = this.selectedInstruction.id;
        } else {
            alert("no id selected");
            return;
        }

        this.http.delete(backendUrl + `delete.php`, {
            params: {
                table_name: this.table_name,
                id: id_to_send,
            },
        }).subscribe((result) => {
            console.log(result);
            this.pullInstructions(this.offset, this.limit);
            this.selectedInstruction = null;
        });
    }

    refresh(offset: number, limit: number): Observable<Instruction[]> {
        return this.http.get<Instruction[]>(backendUrl + `show.php`, {
            params: {
                table_name: this.table_name,
                offset: offset.toString(),
                limit: limit.toString(),
            }
        });
    }

    nextPage() {
        this.refresh(this.offset + this.limit, this.limit).subscribe(Instructions => {
            if (Instructions.length != 0) {
                this.offset += this.limit;
                this.instructions = Instructions;
            }
        });
    }

    prevPage() {
        if (this.offset - this.limit >= 0) {
            this.offset -= this.limit;

            this.pullInstructions(this.offset, this.limit);
        }
    }
}
