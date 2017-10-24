<template>
  <v-container fluid>
    <v-layout row wrap justify-space-around>
      <v-flex xs12 md5 xl3 v-for="c in $root.cocktails" :key="c.name">
        <cocktail-panel :cocktail="c" @order="handleOrder"></cocktail-panel>
      </v-flex>
    </v-layout>

    <v-snackbar :timeout=2000
                :top=true
                :vertical=true
                v-model="snackbar">
      {{ snacktext }}
      <v-btn flat color="pink" @click.native="snackbar = false">Close</v-btn>
    </v-snackbar>
    <order-dialog :order="order" @close="order = null"></order-dialog>
  </v-container>
</template>

<script>
import CocktailPanel from '@/components/CocktailPanel'
import CocktailLoader from '@/components/CocktailLoader'
import OrderDialog from '@/components/OrderDialog'

export default {
  name: 'cocktails',
  data () {
    return {
      snackbar: false,
      snacktext: '',
      order: null
    }
  },
  methods: {
    notify (message) {
      this.snacktext = message
      this.snackbar = true
    },
    handleOrder (order) {
      this.order = order
    }
  },
  components: {
    CocktailPanel,
    CocktailLoader,
    OrderDialog
  }
}
</script>

<style>
</style>
