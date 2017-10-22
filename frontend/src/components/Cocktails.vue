<template>
  <v-container fluid>
    <v-layout row wrap justify-space-around>
      <v-flex xs12 md5 xl3 v-for="c in $root.cocktails" :key="c.name">
        <cocktail-panel :cocktail="c"></cocktail-panel>
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
      snackbar: false,
      snacktext: ''
    }
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
