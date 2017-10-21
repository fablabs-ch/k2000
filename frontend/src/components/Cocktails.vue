<template>
  <v-container fluid>
    <v-layout row wrap>
      <v-flex xs3>
        <v-card v-for="item in items" :key="item">
          <v-card-title primary-title>
            <h4>{{ item }}</h4>
          </v-card-title>
          <v-card-actions>
            <v-btn primary @click="order(item)">Order {{ item }}</v-btn>
          </v-card-actions>
        </v-card>
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
export default {
  name: 'cocktails',
  data: function () {
    return {
      items: ['Vodka', 'Martini'],
      snackbar: false,
      snacktext: ''
    }
  },
  methods: {
    order: function (cocktail) {
      this.notify(cocktail)
    },
    notify: function (message) {
      this.snacktext = message
      this.snackbar = true
    }
  }
}
</script>

<style>
</style>
