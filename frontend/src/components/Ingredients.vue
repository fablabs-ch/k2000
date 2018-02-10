<template>
  <v-container fluid>
    <v-layout column justify-space-around>
      <v-flex md6 offset-md3>
      <h3><img src="../assets/picnic-basket-full-of-raw-vegetables.svg" alt="ingredients"> Ingredients</h3>

        <v-card id="addNewIngridient">
          <v-toolbar dark color="primary">
            <v-toolbar-title class="white--text">Add New Ingridient</v-toolbar-title>
          </v-toolbar>
          <v-card-title>
            <v-layout column justify-space-around>
              <v-list>
                <ingredient-list-item :value="newIngredient"></ingredient-list-item>
              </v-list>
            </v-layout>
          </v-card-title>
          <v-card-actions>
            <v-spacer></v-spacer>
            <v-btn color="primary" @click.native="add" :disabled="newIngredient.name.length === 0">Add</v-btn>
          </v-card-actions>
        </v-card>
        <v-card>
          <v-list two-line>
            <ingredient-list-item :canDelete="true" :value="ingrident" v-for="(ingrident, id) in $root.ingredients" :key="id" @change="save" @delete="deleteItem"></ingredient-list-item>
          </v-list>
       </v-card>
      </v-flex>
    </v-layout>
  </v-container>
</template>

<script>
import IngredientListItem from '@/components/IngredientListItem'

export default {
  data () {
    return {
      newIngredient: this.createNewIngredient()
    }
  },
  methods: {
    createNewIngredient () {
      return {
        type: 'ALCOHOL',
        name: '',
        color: '#FF0000'
      }
    },
    add () {
      this.$http.post('ingredients', this.newIngredient).then(reponse => {
        const savedIngredient = reponse.data
        this.$root.ingredients[savedIngredient.id] = savedIngredient
        this.newIngredient = this.createNewIngredient()
      })
    },
    save (ingredient) {
      this.$http.put(`ingredients/${ingredient.id}`, ingredient).then(reponse => {
        this.$root.notify('Saved!')
      })
    },
    deleteItem (ingredient) {
      this.$http.delete(`ingredients/${ingredient.id}`, ingredient).then(reponse => {
        this.$delete(this.$root.ingredients, ingredient.id)
      })
    }
  },
  components: {
    IngredientListItem
  }
}
</script>

<style scoped>
#addNewIngridient {
  margin-bottom: 40px;
}
</style>
