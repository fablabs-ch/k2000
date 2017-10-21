<template>
  <v-container fluid>
    <v-layout row wrap>
      <v-flex xs12 v-for="c in cocktails" :key="c.name">
        <cocktail-panel :cocktail="c" :ingredients="ingredients"></cocktail-panel>
      </v-flex>
    </v-layout>

    <v-snackbar :timeout=2000
                :top=true
                :vertical=true
                v-model="snackbar">
      {{ snacktext }}
      <v-btn flat color="pink" @click.native="snackbar = false">Close</v-btn>
    </v-snackbar>
  </v-container>
</template>

<script>
import cocktailPanel from '@/components/CocktailPanel'
export default {
  name: 'cocktails',
  data () {
    return {
      cocktails: [],
      ingredients: {},
      snackbar: false,
      snacktext: ''
    }
  },
  mounted () {
    const cocktailsDB = require('../../static/cocktail.json')
    this.cocktails = cocktailsDB.recipes
    this.ingredients = cocktailsDB.ingredients.reduce((ingredients, i) => {
      ingredients[i.id] = i
      return ingredients
    }, {})
  },
  methods: {
    notify (message) {
      this.snacktext = message
      this.snackbar = true
    }
  },
  components: {
    cocktailPanel
  }
}
</script>

<style>
</style>
